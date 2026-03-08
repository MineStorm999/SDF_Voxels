import Tree;

StructuredBuffer<Tree> tree;

[shader("compute")]
[numthreads(8, 8, 1)]
void RayTrace(uint3 threadId: SV_DispatchThreadID)
{
}
