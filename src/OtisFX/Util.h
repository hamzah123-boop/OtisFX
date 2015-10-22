// Stuff all/most of OtisFX shared shaders need
// Based on MFX
NAMESPACE_ENTER(OFX)
#define OFX_SETTINGS_DEF "ReShade/OtisFX.cfg"
#define OFX_SETTINGS_UNDEF "ReShade/OtisFX.undef" 

#include OFX_SETTINGS_DEF

#if( HDR_MODE == 0)
 #define RENDERMODE RGBA8
#elif( HDR_MODE == 1)
 #define RENDERMODE RGBA16F
#else
 #define RENDERMODE RGBA32F
#endif

//textures
texture   OFX_FragmentBuffer1 	{ Width = BUFFER_WIDTH; Height = BUFFER_HEIGHT; MipLevels = 8; Format = RENDERMODE;};	
texture   OFX_FragmentBuffer2 	{ Width = BUFFER_WIDTH; Height = BUFFER_HEIGHT; MipLevels = 8; Format = RENDERMODE;};	

//samplers
sampler2D OFX_SamplerFragmentBuffer2
{
	Texture = OFX_FragmentBuffer2;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

sampler2D OFX_SamplerFragmentBuffer1
{
	Texture = OFX_FragmentBuffer1;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Functions														     //
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void PS_OFX_Init(float4 vpos : SV_Position, float2 texcoord : TEXCOORD, out float4 colFragment : SV_Target0) 
{
	colFragment = tex2D(RFX_originalColor, texcoord.xy);
}

float4 PS_OFX_Overlay(float4 vpos : SV_Position, float2 texcoord : TEXCOORD) : SV_Target
{
	return tex2D(OFX_SamplerFragmentBuffer2, texcoord.xy);
}

#if USE_EMPHASIZE
technique OFX_Init_Tech  < enabled = true; >
{
	pass Init_OFX_FragmentBuffer2
	{
		VertexShader = RFX_VS_PostProcess;			
		PixelShader = PS_OFX_Init;
		RenderTarget = OFX_FragmentBuffer2;
	}
	pass Init_OFX_FragmentBuffer1
	{
		VertexShader = RFX_VS_PostProcess;			
		PixelShader = PS_OFX_Init;
		RenderTarget = OFX_FragmentBuffer1;
	}
}
#endif

#include OFX_SETTINGS_UNDEF

NAMESPACE_LEAVE()

#pragma message "OtisFX 0.1 by Otis / Infuse Project\n\n"