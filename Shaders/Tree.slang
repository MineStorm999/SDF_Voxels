import childPtrs;

StructuredBuffer<uint> bitMasks;
StructuredBuffer<ChildPtr> childPtrs;

[format("rgba8ui")]
Texture2DArray<float4> data;

struct Tree {
    int Traverse() { //TODO
        return 1;
    }
}