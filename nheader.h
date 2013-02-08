typedef struct{
    uint32_t seqNum;
    uint16_t checksum;
    uint8_t flag;

    uint8_t destHandleLength;
    uint8_t *destHandle;

    uint8_t sendHandleLength;
    uint8_t *sendHandle;

    uint8_t *text;
}header;


