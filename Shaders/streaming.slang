
struct StreamingRequest {
    uint parentID;
    uint childID;
}

RWStructuredBuffer<StreamingRequest> reqBuffer;

namespace streaming {
    static void AddRequest(uint parentID, uint childID) {
        
    }
}