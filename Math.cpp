#include "SDK.h"

void inline SinCos( float radians, float *sine, float *cosine )
{
	*sine = sin( radians );
	*cosine = cos( radians );
}

void VectorAngles( const Vector& forward, QAngle &angles )
{
	if( forward[ 1 ] == 0.0f && forward[ 0 ] == 0.0f )
	{
		angles[ 0 ] = ( forward[ 2 ] > 0.0f ) ? 270.0f : 90.0f;
		angles[ 1 ] = 0.0f;
	}
	else
	{
		float len2d = sseSqrt( square( forward[ 0 ] ) + square( forward[ 1 ] ) );

		angles[ 0 ] = RAD2DEG( atan2f( -forward[ 2 ], len2d ) );
		angles[ 1 ] = RAD2DEG( atan2f( forward[ 1 ], forward[ 0 ] ) );

		if( angles[ 0 ] < 0.0f ) angles[ 0 ] += 360.0f;
		if( angles[ 1 ] < 0.0f ) angles[ 1 ] += 360.0f;
	}

	angles[ 2 ] = 0.0f;
}

void AngleVectors2D(Vector& vecAngles, Vector& vecForward)
{
	float sp, sy, cp, cy;
	SinCos(static_cast<float>(vecAngles[1] * (M_PI / 180.f)), &sy, &cy);
	SinCos(static_cast<float>(vecAngles[0] * (M_PI / 180.f)), &sp, &cp);

	vecForward[0] = cp * cy;
	vecForward[1] = cp * sy;
	vecForward[2] = -sp;
}

void VectorAngles2D(Vector& vecForward, Vector& vecAngles)
{
	Vector vecView;
	if (vecForward[1] == 0.f && vecForward[0] == 0.f)
	{
		vecView[0] = 0.f;
		vecView[1] = 0.f;
	}
	else
	{
		vecView[1] = atan2(vecForward[1], vecForward[0]) * 180.f / M_PI;

		if (vecView[1] < 0.f)
			vecView[1] += 360.f;

		vecView[2] = sqrt(vecForward[0] * vecForward[0] + vecForward[1] * vecForward[1]);

		vecView[0] = atan2(vecForward[2], vecView[2]) * 180.f / M_PI;
	}

	vecAngles[0] = -vecView[0];
	vecAngles[1] = vecView[1];
	vecAngles[2] = 0.f;
}

void NormalizeAngles2D(Vector& vecAngles)
{
	for (auto i = 0; i < 3; ++i)
	{
		while (vecAngles[i] > 180.f)
			vecAngles[i] -= 360.f;

		while (vecAngles[i] < -180.f)
			vecAngles[i] += 360.f;
	}

	vecAngles[2] = 0.f;
}

void AngleVectors( const QAngle &angles, Vector *forward )
{
	float sp, sy, cp, cy;

	SinCos( DEG2RAD( angles[ YAW ] ), &sy, &cy );
	SinCos( DEG2RAD( angles[ PITCH ] ), &sp, &cp );

	forward->x = cp*cy;
	forward->y = cp*sy;
	forward->z = -sp;
}

void AngleVectors( const QAngle &angles, Vector *forward, Vector *right, Vector *up )
{
	float sr, sp, sy, cr, cp, cy;

	SinCos( DEG2RAD( angles[ YAW ] ), &sy, &cy );
	SinCos( DEG2RAD( angles[ PITCH ] ), &sp, &cp );
	SinCos( DEG2RAD( angles[ ROLL ] ), &sr, &cr );

	if( forward )
	{
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	if( right )
	{
		right->x = ( -1 * sr*sp*cy + -1 * cr*-sy );
		right->y = ( -1 * sr*sp*sy + -1 * cr*cy );
		right->z = -1 * sr*cp;
	}

	if( up )
	{
		up->x = ( cr*sp*cy + -sr*-sy );
		up->y = ( cr*sp*sy + -sr*cy );
		up->z = cr*cp;
	}
}

float GetFov( const QAngle& viewAngle, const QAngle& aimAngle )
{
	Vector ang, aim;

	AngleVectors( viewAngle, &aim  );
	AngleVectors( aimAngle, &ang );

	return RAD2DEG( acos( aim.Dot( ang ) / aim.LengthSqr() ) );
}


__forceinline __m128 _mm_hadd4_ps(__m128 i)
{
	__m128 t = i;
	t = _mm_movehl_ps(t, i);
	i = _mm_add_ps(i, t);
	t = _mm_shuffle_ps(i, i, 0x55);
	i = _mm_add_ps(i, t);
	return i;
}

#define RADPI 57.295779513082f

void CalcAngle(Vector vecSrc, const Vector vecDst, QAngle& vecAngle)
{
	auto vecDelta = vecSrc - vecDst;

	auto mThis = _mm_setr_ps(vecDelta.x, vecDelta.y, 0.f, 0.f);
	auto mResult = _mm_mul_ps(mThis, mThis);
	auto mPreHyp = _mm_hadd4_ps(mResult);
	auto mHypMM = _mm_sqrt_ss(mPreHyp);
	auto flHyp = mHypMM.m128_f32[0];

	vecAngle.x = atan(vecDelta.z / flHyp) * RADPI;
	vecAngle.y = atan(vecDelta.y / vecDelta.x) * RADPI;
	vecAngle.z = 0.f;
	if (vecDelta.x >= 0.f)
	{
		vecAngle.y += 180.f;
	}
}

float VectorDistance( Vector v1, Vector v2 )
{
	return FASTSQRT( pow( v1.x - v2.x, 2 ) + pow( v1.y - v2.y, 2 ) + pow( v1.z - v2.z, 2 ) );
}

void VectorTransform( Vector& in1, matrix3x4a_t& in2, Vector &out )
{
	out.x = in1.Dot( in2.m_flMatVal[ 0 ] ) + in2.m_flMatVal[ 0 ][ 3 ];
	out.y = in1.Dot( in2.m_flMatVal[ 1 ] ) + in2.m_flMatVal[ 1 ][ 3 ];
	out.z = in1.Dot( in2.m_flMatVal[ 2 ] ) + in2.m_flMatVal[ 2 ][ 3 ];
}

float GetDelta( float hspeed, float maxspeed, float airaccelerate )
{
	auto term = ( 30.0 - ( airaccelerate * maxspeed / 66.0 ) ) / hspeed;

	if( term < 1.0f && term > -1.0f ) {
		return acos( term );
	}

	return 0.f;
}

inline float RandFloat( float M, float N )
{
	return static_cast<float>(M + ( rand() / ( RAND_MAX / ( N - M ) ) ));
}

inline Vector ExtrapolateTick( Vector p0, Vector v0 )
{
	return p0 + ( v0 * Globals->interval_per_tick );
}
