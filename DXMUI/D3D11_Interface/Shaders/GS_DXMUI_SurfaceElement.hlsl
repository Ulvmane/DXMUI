struct GSOutput
{
	float4 myPosition : SV_POSITION;
    float4 myColor : COLOR;
    float2 myUV : UV;
    bool   myHasTexture : HAS_TEXTURE;
    float TRASH : T;
};

cbuffer ElementBuffer : register(b0)
{
    float4 myTextureRect : RECT;
    float4 myColor : COLOR;
    float2 myElementPosition : SV_POSITION;
    float2 myElementSize : SIZE;
    float2 myElementPivot : PIVOT;
    bool   myHasTexture : HAS_TEXTURE;
    float TRASH : TRASH;
}

[maxvertexcount(4)]
void main(
	point float4 input[1] : SV_POSITION, 
	inout TriangleStream< GSOutput > output
)
{
    float dX = (myTextureRect.z - myTextureRect.x);
    float dY = (myTextureRect.y - myTextureRect.w);
    
    float lowX = (-2 * myElementPivot.x);
    float HighX = (2 * (1 - myElementPivot.x));
    
    float lowY = (-2 * (myElementPivot.y));
    float HighY = (2 * (1 - myElementPivot.y));
    
    const float2 offsets[4] =
    {
        { HighX * dX, HighY * dY },
        { lowX * dX, HighY * dY },
        { HighX * dX, lowY * dY },
        { lowX * dX, lowY * dY }
    };
    
    
    const float2 uvs[4] =
    {
        { myTextureRect.z, myTextureRect.w },
        { myTextureRect.x, myTextureRect.w },
        { myTextureRect.z, myTextureRect.y },
        { myTextureRect.x, myTextureRect.y }
    };
    
    
    float4 pos;
    
    pos.xy = (2 * myElementPosition) - 1; //Norrmalize screenspace
    pos.y *= -1; //Adjust for inverted y axis
    pos.zw = 1; //Reset depth to guarantee 1 to 1 results
    
    
    for (int i = 0; i < 4; i++)
    {
        GSOutput vertex;
        vertex.myPosition = pos;
        vertex.myPosition.xy += offsets[i] * myElementSize;
        vertex.myColor = myColor;
        vertex.myUV = uvs[i];
        vertex.myHasTexture = myHasTexture;
        vertex.TRASH.x = 0;
        output.Append(vertex);
    }
}