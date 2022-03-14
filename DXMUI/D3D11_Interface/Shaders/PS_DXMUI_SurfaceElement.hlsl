SamplerState defaultSampler : register(s0);
Texture2D Sprite : register(t0);

struct PixelOutput
{
    float4 myColor : SV_TARGET;
};


struct GSOutput
{
    float4 myPosition : SV_POSITION;
    float4 myColor : COLOR;
    float2 myUV : UV;
    bool myHasTexture : HAS_TEXTURE;
    float TRASH : T;
};


PixelOutput main(GSOutput input)
{
    PixelOutput output;
    output.myColor = input.myColor;
    if (input.myHasTexture)
    {
        output.myColor *= Sprite.Sample(defaultSampler, input.myUV.xy).rgba;
    }
    
    return output;
}