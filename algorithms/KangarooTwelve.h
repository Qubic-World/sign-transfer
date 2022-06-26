#pragma once

////////// KangarooTwelve \\\\\\\\\\


#include <cstdint>
#include <memory>


#if defined(_MSC_VER)
#define ROL64(a, offset) _rotl64(a, offset)
#else
#define ROL64(a, offset) ((((unsigned long long)a) << offset) ^ (((unsigned long long)a) >> (64 - offset)))
#endif

static constexpr uint64_t KeccakF1600RoundConstant0{ 0x000000008000808bULL };
static constexpr uint64_t KeccakF1600RoundConstant1{ 0x800000000000008bULL };
static constexpr uint64_t KeccakF1600RoundConstant2{ 0x8000000000008089ULL };
static constexpr uint64_t KeccakF1600RoundConstant3{ 0x8000000000008003ULL };
static constexpr uint64_t KeccakF1600RoundConstant4{ 0x8000000000008002ULL };
static constexpr uint64_t KeccakF1600RoundConstant5{ 0x8000000000000080ULL };
static constexpr uint64_t KeccakF1600RoundConstant6{ 0x000000000000800aULL };
static constexpr uint64_t KeccakF1600RoundConstant7{ 0x800000008000000aULL };
static constexpr uint64_t KeccakF1600RoundConstant8{ 0x8000000080008081ULL };
static constexpr uint64_t KeccakF1600RoundConstant9{ 0x8000000000008080ULL };
static constexpr uint64_t KeccakF1600RoundConstant10{ 0x0000000080000001ULL };

#define declareABCDE \
    unsigned long long Aba, Abe, Abi, Abo, Abu; \
    unsigned long long Aga, Age, Agi, Ago, Agu; \
    unsigned long long Aka, Ake, Aki, Ako, Aku; \
    unsigned long long Ama, Ame, Ami, Amo, Amu; \
    unsigned long long Asa, Ase, Asi, Aso, Asu; \
    unsigned long long Bba, Bbe, Bbi, Bbo, Bbu; \
    unsigned long long Bga, Bge, Bgi, Bgo, Bgu; \
    unsigned long long Bka, Bke, Bki, Bko, Bku; \
    unsigned long long Bma, Bme, Bmi, Bmo, Bmu; \
    unsigned long long Bsa, Bse, Bsi, Bso, Bsu; \
    unsigned long long Ca, Ce, Ci, Co, Cu; \
    unsigned long long Da, De, Di, Do, Du; \
    unsigned long long Eba, Ebe, Ebi, Ebo, Ebu; \
    unsigned long long Ega, Ege, Egi, Ego, Egu; \
    unsigned long long Eka, Eke, Eki, Eko, Eku; \
    unsigned long long Ema, Eme, Emi, Emo, Emu; \
    unsigned long long Esa, Ese, Esi, Eso, Esu; \

#define thetaRhoPiChiIotaPrepareTheta(i, A, E) \
    Da = Cu^ROL64(Ce, 1); \
    De = Ca^ROL64(Ci, 1); \
    Di = Ce^ROL64(Co, 1); \
    Do = Ci^ROL64(Cu, 1); \
    Du = Co^ROL64(Ca, 1); \
    A##ba ^= Da; \
    Bba = A##ba; \
    A##ge ^= De; \
    Bbe = ROL64(A##ge, 44); \
    A##ki ^= Di; \
    Bbi = ROL64(A##ki, 43); \
    A##mo ^= Do; \
    Bbo = ROL64(A##mo, 21); \
    A##su ^= Du; \
    Bbu = ROL64(A##su, 14); \
    E##ba =   Bba ^((~Bbe)&  Bbi ); \
    E##ba ^= KeccakF1600RoundConstant##i; \
    Ca = E##ba; \
    E##be =   Bbe ^((~Bbi)&  Bbo ); \
    Ce = E##be; \
    E##bi =   Bbi ^((~Bbo)&  Bbu ); \
    Ci = E##bi; \
    E##bo =   Bbo ^((~Bbu)&  Bba ); \
    Co = E##bo; \
    E##bu =   Bbu ^((~Bba)&  Bbe ); \
    Cu = E##bu; \
    A##bo ^= Do; \
    Bga = ROL64(A##bo, 28); \
    A##gu ^= Du; \
    Bge = ROL64(A##gu, 20); \
    A##ka ^= Da; \
    Bgi = ROL64(A##ka, 3); \
    A##me ^= De; \
    Bgo = ROL64(A##me, 45); \
    A##si ^= Di; \
    Bgu = ROL64(A##si, 61); \
    E##ga =   Bga ^((~Bge)&  Bgi ); \
    Ca ^= E##ga; \
    E##ge =   Bge ^((~Bgi)&  Bgo ); \
    Ce ^= E##ge; \
    E##gi =   Bgi ^((~Bgo)&  Bgu ); \
    Ci ^= E##gi; \
    E##go =   Bgo ^((~Bgu)&  Bga ); \
    Co ^= E##go; \
    E##gu =   Bgu ^((~Bga)&  Bge ); \
    Cu ^= E##gu; \
    A##be ^= De; \
    Bka = ROL64(A##be, 1); \
    A##gi ^= Di; \
    Bke = ROL64(A##gi, 6); \
    A##ko ^= Do; \
    Bki = ROL64(A##ko, 25); \
    A##mu ^= Du; \
    Bko = ROL64(A##mu, 8); \
    A##sa ^= Da; \
    Bku = ROL64(A##sa, 18); \
    E##ka =   Bka ^((~Bke)&  Bki ); \
    Ca ^= E##ka; \
    E##ke =   Bke ^((~Bki)&  Bko ); \
    Ce ^= E##ke; \
    E##ki =   Bki ^((~Bko)&  Bku ); \
    Ci ^= E##ki; \
    E##ko =   Bko ^((~Bku)&  Bka ); \
    Co ^= E##ko; \
    E##ku =   Bku ^((~Bka)&  Bke ); \
    Cu ^= E##ku; \
    A##bu ^= Du; \
    Bma = ROL64(A##bu, 27); \
    A##ga ^= Da; \
    Bme = ROL64(A##ga, 36); \
    A##ke ^= De; \
    Bmi = ROL64(A##ke, 10); \
    A##mi ^= Di; \
    Bmo = ROL64(A##mi, 15); \
    A##so ^= Do; \
    Bmu = ROL64(A##so, 56); \
    E##ma =   Bma ^((~Bme)&  Bmi ); \
    Ca ^= E##ma; \
    E##me =   Bme ^((~Bmi)&  Bmo ); \
    Ce ^= E##me; \
    E##mi =   Bmi ^((~Bmo)&  Bmu ); \
    Ci ^= E##mi; \
    E##mo =   Bmo ^((~Bmu)&  Bma ); \
    Co ^= E##mo; \
    E##mu =   Bmu ^((~Bma)&  Bme ); \
    Cu ^= E##mu; \
    A##bi ^= Di; \
    Bsa = ROL64(A##bi, 62); \
    A##go ^= Do; \
    Bse = ROL64(A##go, 55); \
    A##ku ^= Du; \
    Bsi = ROL64(A##ku, 39); \
    A##ma ^= Da; \
    Bso = ROL64(A##ma, 41); \
    A##se ^= De; \
    Bsu = ROL64(A##se, 2); \
    E##sa =   Bsa ^((~Bse)&  Bsi ); \
    Ca ^= E##sa; \
    E##se =   Bse ^((~Bsi)&  Bso ); \
    Ce ^= E##se; \
    E##si =   Bsi ^((~Bso)&  Bsu ); \
    Ci ^= E##si; \
    E##so =   Bso ^((~Bsu)&  Bsa ); \
    Co ^= E##so; \
    E##su =   Bsu ^((~Bsa)&  Bse ); \
    Cu ^= E##su; \

#define copyFromState(state) \
    Aba = state[ 0]; \
    Abe = state[ 1]; \
    Abi = state[ 2]; \
    Abo = state[ 3]; \
    Abu = state[ 4]; \
    Aga = state[ 5]; \
    Age = state[ 6]; \
    Agi = state[ 7]; \
    Ago = state[ 8]; \
    Agu = state[ 9]; \
    Aka = state[10]; \
    Ake = state[11]; \
    Aki = state[12]; \
    Ako = state[13]; \
    Aku = state[14]; \
    Ama = state[15]; \
    Ame = state[16]; \
    Ami = state[17]; \
    Amo = state[18]; \
    Amu = state[19]; \
    Asa = state[20]; \
    Ase = state[21]; \
    Asi = state[22]; \
    Aso = state[23]; \
    Asu = state[24]; \

#define copyToState(state) \
    state[ 0] = Aba; \
    state[ 1] = Abe; \
    state[ 2] = Abi; \
    state[ 3] = Abo; \
    state[ 4] = Abu; \
    state[ 5] = Aga; \
    state[ 6] = Age; \
    state[ 7] = Agi; \
    state[ 8] = Ago; \
    state[ 9] = Agu; \
    state[10] = Aka; \
    state[11] = Ake; \
    state[12] = Aki; \
    state[13] = Ako; \
    state[14] = Aku; \
    state[15] = Ama; \
    state[16] = Ame; \
    state[17] = Ami; \
    state[18] = Amo; \
    state[19] = Amu; \
    state[20] = Asa; \
    state[21] = Ase; \
    state[22] = Asi; \
    state[23] = Aso; \
    state[24] = Asu; \

#define rounds12 \
    Ca = Aba^Aga^Aka^Ama^Asa; \
    Ce = Abe^Age^Ake^Ame^Ase; \
    Ci = Abi^Agi^Aki^Ami^Asi; \
    Co = Abo^Ago^Ako^Amo^Aso; \
    Cu = Abu^Agu^Aku^Amu^Asu; \
    thetaRhoPiChiIotaPrepareTheta(0, A, E) \
    thetaRhoPiChiIotaPrepareTheta(1, E, A) \
    thetaRhoPiChiIotaPrepareTheta(2, A, E) \
    thetaRhoPiChiIotaPrepareTheta(3, E, A) \
    thetaRhoPiChiIotaPrepareTheta(4, A, E) \
    thetaRhoPiChiIotaPrepareTheta(5, E, A) \
    thetaRhoPiChiIotaPrepareTheta(6, A, E) \
    thetaRhoPiChiIotaPrepareTheta(7, E, A) \
    thetaRhoPiChiIotaPrepareTheta(8, A, E) \
    thetaRhoPiChiIotaPrepareTheta(9, E, A) \
    thetaRhoPiChiIotaPrepareTheta(10, A, E) \
    Da = Cu^ROL64(Ce, 1); \
    De = Ca^ROL64(Ci, 1); \
    Di = Ce^ROL64(Co, 1); \
    Do = Ci^ROL64(Cu, 1); \
    Du = Co^ROL64(Ca, 1); \
    Eba ^= Da; \
    Bba = Eba; \
    Ege ^= De; \
    Bbe = ROL64(Ege, 44); \
    Eki ^= Di; \
    Bbi = ROL64(Eki, 43); \
    Emo ^= Do; \
    Bbo = ROL64(Emo, 21); \
    Esu ^= Du; \
    Bbu = ROL64(Esu, 14); \
    Aba =   Bba ^((~Bbe)&  Bbi ); \
    Aba ^= 0x8000000080008008ULL; \
    Abe =   Bbe ^((~Bbi)&  Bbo ); \
    Abi =   Bbi ^((~Bbo)&  Bbu ); \
    Abo =   Bbo ^((~Bbu)&  Bba ); \
    Abu =   Bbu ^((~Bba)&  Bbe ); \
    Ebo ^= Do; \
    Bga = ROL64(Ebo, 28); \
    Egu ^= Du; \
    Bge = ROL64(Egu, 20); \
    Eka ^= Da; \
    Bgi = ROL64(Eka, 3); \
    Eme ^= De; \
    Bgo = ROL64(Eme, 45); \
    Esi ^= Di; \
    Bgu = ROL64(Esi, 61); \
    Aga =   Bga ^((~Bge)&  Bgi ); \
    Age =   Bge ^((~Bgi)&  Bgo ); \
    Agi =   Bgi ^((~Bgo)&  Bgu ); \
    Ago =   Bgo ^((~Bgu)&  Bga ); \
    Agu =   Bgu ^((~Bga)&  Bge ); \
    Ebe ^= De; \
    Bka = ROL64(Ebe, 1); \
    Egi ^= Di; \
    Bke = ROL64(Egi, 6); \
    Eko ^= Do; \
    Bki = ROL64(Eko, 25); \
    Emu ^= Du; \
    Bko = ROL64(Emu, 8); \
    Esa ^= Da; \
    Bku = ROL64(Esa, 18); \
    Aka =   Bka ^((~Bke)&  Bki ); \
    Ake =   Bke ^((~Bki)&  Bko ); \
    Aki =   Bki ^((~Bko)&  Bku ); \
    Ako =   Bko ^((~Bku)&  Bka ); \
    Aku =   Bku ^((~Bka)&  Bke ); \
    Ebu ^= Du; \
    Bma = ROL64(Ebu, 27); \
    Ega ^= Da; \
    Bme = ROL64(Ega, 36); \
    Eke ^= De; \
    Bmi = ROL64(Eke, 10); \
    Emi ^= Di; \
    Bmo = ROL64(Emi, 15); \
    Eso ^= Do; \
    Bmu = ROL64(Eso, 56); \
    Ama =   Bma ^((~Bme)&  Bmi ); \
    Ame =   Bme ^((~Bmi)&  Bmo ); \
    Ami =   Bmi ^((~Bmo)&  Bmu ); \
    Amo =   Bmo ^((~Bmu)&  Bma ); \
    Amu =   Bmu ^((~Bma)&  Bme ); \
    Ebi ^= Di; \
    Bsa = ROL64(Ebi, 62); \
    Ego ^= Do; \
    Bse = ROL64(Ego, 55); \
    Eku ^= Du; \
    Bsi = ROL64(Eku, 39); \
    Ema ^= Da; \
    Bso = ROL64(Ema, 41); \
    Ese ^= De; \
    Bsu = ROL64(Ese, 2); \
    Asa =   Bsa ^((~Bse)&  Bsi ); \
    Ase =   Bse ^((~Bsi)&  Bso ); \
    Asi =   Bsi ^((~Bso)&  Bsu ); \
    Aso =   Bso ^((~Bsu)&  Bsa ); \
    Asu =   Bsu ^((~Bsa)&  Bse ); \


static constexpr uint8_t K12_security{ 128 };
static constexpr uint16_t K12_capacity{ 2 * K12_security };
static constexpr uint8_t K12_capacityInBytes{ K12_capacity / 8 };
static constexpr uint16_t K12_rate{ 1600 - K12_capacity };
static constexpr uint8_t K12_rateInBytes{ K12_rate / 8 };
static constexpr uint8_t K12_rateInLanes{ K12_rate / 64 };
static constexpr uint16_t K12_chunkSize{ 8192 };
static constexpr uint8_t K12_suffixLeaf{ 0x0B };

typedef struct
{
	unsigned char state[200];
	unsigned char byteIOIndex;
	unsigned char squeezing;
} KangarooTwelve_F;

typedef struct
{
	KangarooTwelve_F queueNode;
	KangarooTwelve_F finalNode;
	unsigned long long blockNumber;
	unsigned int queueAbsorbedLen;
} KangarooTwelve_Instance;

inline static void KeccakP1600_Permute_12rounds(void* state)
{
    declareABCDE
        unsigned long long* stateAsLanes = (unsigned long long*)state;
    copyFromState(stateAsLanes)
        rounds12
        copyToState(stateAsLanes)
}

inline static void KeccakP1600_ExtractBytes(const void* state, unsigned char* data, unsigned int offset, unsigned int length)
{
    if (!offset)
    {
        memcpy(data, const_cast<void*>(state), length & 0xFFFFFFF8);
        memcpy(data + (length & 0xFFFFFFF8), &static_cast<unsigned long long*>(const_cast<void*>(state))[length >> 3], length & 7);
    }
    else
    {
        unsigned int _sizeLeft = length;
        unsigned int _lanePosition = offset >> 3;
        unsigned int _offsetInLane = offset & 7;
        unsigned char* _curData = data;
        while (_sizeLeft > 0)
        {
            unsigned int _bytesInLane = 8 - _offsetInLane;
            if (_bytesInLane > _sizeLeft)
            {
                _bytesInLane = _sizeLeft;
            }
            memcpy(_curData, (unsigned char*)(&(((unsigned long long*)state)[_lanePosition])) + _offsetInLane, _bytesInLane);
            _sizeLeft -= _bytesInLane;
            _lanePosition++;
            _offsetInLane = 0;
            _curData += _bytesInLane;
        }
    }
}

inline static void KangarooTwelve_F_Absorb(KangarooTwelve_F* instance, unsigned char* data, unsigned long long dataByteLen)
{
    unsigned long long i = 0;
    while (i < dataByteLen)
    {
        if (!instance->byteIOIndex && dataByteLen >= i + K12_rateInBytes)
        {
            declareABCDE
                unsigned long long* stateAsLanes = (unsigned long long*)instance->state;
            copyFromState(stateAsLanes)
                unsigned long long modifiedDataByteLen = dataByteLen - i;
            while (modifiedDataByteLen >= K12_rateInBytes)
            {
                Aba ^= ((unsigned long long*)data)[0];
                Abe ^= ((unsigned long long*)data)[1];
                Abi ^= ((unsigned long long*)data)[2];
                Abo ^= ((unsigned long long*)data)[3];
                Abu ^= ((unsigned long long*)data)[4];
                Aga ^= ((unsigned long long*)data)[5];
                Age ^= ((unsigned long long*)data)[6];
                Agi ^= ((unsigned long long*)data)[7];
                Ago ^= ((unsigned long long*)data)[8];
                Agu ^= ((unsigned long long*)data)[9];
                Aka ^= ((unsigned long long*)data)[10];
                Ake ^= ((unsigned long long*)data)[11];
                Aki ^= ((unsigned long long*)data)[12];
                Ako ^= ((unsigned long long*)data)[13];
                Aku ^= ((unsigned long long*)data)[14];
                Ama ^= ((unsigned long long*)data)[15];
                Ame ^= ((unsigned long long*)data)[16];
                Ami ^= ((unsigned long long*)data)[17];
                Amo ^= ((unsigned long long*)data)[18];
                Amu ^= ((unsigned long long*)data)[19];
                Asa ^= ((unsigned long long*)data)[20];
                rounds12
                    data += K12_rateInBytes;
                modifiedDataByteLen -= K12_rateInBytes;
            }
            copyToState(stateAsLanes)
                i = dataByteLen - modifiedDataByteLen;
        }
        else
        {
            unsigned char partialBlock;
            if ((dataByteLen - i) + instance->byteIOIndex > K12_rateInBytes)
            {
                partialBlock = K12_rateInBytes - instance->byteIOIndex;
            }
            else
            {
                partialBlock = (unsigned char)(dataByteLen - i);
            }
            i += partialBlock;

            if (!instance->byteIOIndex)
            {
                unsigned int j = 0;
                for (; (j + 8) <= (unsigned int)(partialBlock >> 3); j += 8)
                {
                    ((unsigned long long*)instance->state)[j + 0] ^= ((unsigned long long*)data)[j + 0];
                    ((unsigned long long*)instance->state)[j + 1] ^= ((unsigned long long*)data)[j + 1];
                    ((unsigned long long*)instance->state)[j + 2] ^= ((unsigned long long*)data)[j + 2];
                    ((unsigned long long*)instance->state)[j + 3] ^= ((unsigned long long*)data)[j + 3];
                    ((unsigned long long*)instance->state)[j + 4] ^= ((unsigned long long*)data)[j + 4];
                    ((unsigned long long*)instance->state)[j + 5] ^= ((unsigned long long*)data)[j + 5];
                    ((unsigned long long*)instance->state)[j + 6] ^= ((unsigned long long*)data)[j + 6];
                    ((unsigned long long*)instance->state)[j + 7] ^= ((unsigned long long*)data)[j + 7];
                }
                for (; (j + 4) <= (unsigned int)(partialBlock >> 3); j += 4)
                {
                    ((unsigned long long*)instance->state)[j + 0] ^= ((unsigned long long*)data)[j + 0];
                    ((unsigned long long*)instance->state)[j + 1] ^= ((unsigned long long*)data)[j + 1];
                    ((unsigned long long*)instance->state)[j + 2] ^= ((unsigned long long*)data)[j + 2];
                    ((unsigned long long*)instance->state)[j + 3] ^= ((unsigned long long*)data)[j + 3];
                }
                for (; (j + 2) <= (unsigned int)(partialBlock >> 3); j += 2)
                {
                    ((unsigned long long*)instance->state)[j + 0] ^= ((unsigned long long*)data)[j + 0];
                    ((unsigned long long*)instance->state)[j + 1] ^= ((unsigned long long*)data)[j + 1];
                }
                if (j < (unsigned int)(partialBlock >> 3))
                {
                    ((unsigned long long*)instance->state)[j + 0] ^= ((unsigned long long*)data)[j + 0];
                }
                if (partialBlock & 7)
                {
                    if ((partialBlock & 7) == 1)
                    {
                        ((unsigned long long*)instance->state)[partialBlock >> 3] ^= ((unsigned long long)data[partialBlock & 0xFFFFFFF8]);
                    }
                    else
                    {
                        unsigned long long lane = 0;
                        memcpy(&lane, data + (partialBlock & 0xFFFFFFF8), partialBlock & 7);
                        ((unsigned long long*)instance->state)[partialBlock >> 3] ^= lane;
                    }
                }
            }
            else
            {
                unsigned int _sizeLeft = partialBlock;
                unsigned int _lanePosition = instance->byteIOIndex >> 3;
                unsigned int _offsetInLane = instance->byteIOIndex & 7;
                const unsigned char* _curData = data;
                while (_sizeLeft > 0)
                {
                    unsigned int _bytesInLane = 8 - _offsetInLane;
                    if (_bytesInLane > _sizeLeft)
                    {
                        _bytesInLane = _sizeLeft;
                    }
                    if (_bytesInLane)
                    {
                        if (_bytesInLane == 1)
                        {
                            ((unsigned long long*)instance->state)[_lanePosition] ^= (((unsigned long long)_curData[0]) << (_offsetInLane << 3));
                        }
                        else
                        {
                            unsigned long long lane = 0;
                            memcpy(&lane, (void*)_curData, _bytesInLane);
                            ((unsigned long long*)instance->state)[_lanePosition] ^= (lane << (_offsetInLane << 3));
                        }
                    }
                    _sizeLeft -= _bytesInLane;
                    _lanePosition++;
                    _offsetInLane = 0;
                    _curData += _bytesInLane;
                }
            }

            data += partialBlock;
            instance->byteIOIndex += partialBlock;
            if (instance->byteIOIndex == K12_rateInBytes)
            {
                KeccakP1600_Permute_12rounds(instance->state);
                instance->byteIOIndex = 0;
            }
        }
    }
}

inline static void KangarooTwelve_F_AbsorbLastFewBits(KangarooTwelve_F* instance, unsigned char delimitedData)
{
    instance->state[instance->byteIOIndex] ^= delimitedData;
    if ((delimitedData >= 0x80) && (instance->byteIOIndex == (K12_rateInBytes - 1)))
    {
        KeccakP1600_Permute_12rounds(instance->state);
    }
    instance->state[K12_rateInBytes - 1] ^= 0x80;
    KeccakP1600_Permute_12rounds(instance->state);
    instance->byteIOIndex = 0;
    instance->squeezing = 1;
}

inline static void KangarooTwelve_F_Squeeze(KangarooTwelve_F* instance, unsigned char* data, unsigned long long dataByteLen)
{
    if (!instance->squeezing)
    {
        KangarooTwelve_F_AbsorbLastFewBits(instance, 0x01);
    }

    unsigned long long i = 0;
    unsigned char* curData = data;
    while (i < dataByteLen)
    {
        if ((instance->byteIOIndex == K12_rateInBytes) && (dataByteLen >= (i + K12_rateInBytes)))
        {
            unsigned long long j;
            for (j = dataByteLen - i; j >= K12_rateInBytes; j -= K12_rateInBytes)
            {
                KeccakP1600_Permute_12rounds(instance->state);
                KeccakP1600_ExtractBytes(instance->state, curData, 0, K12_rateInBytes);
                curData += K12_rateInBytes;
            }
            i = dataByteLen - j;
        }
        else
        {
            if (instance->byteIOIndex == K12_rateInBytes)
            {
                KeccakP1600_Permute_12rounds(instance->state);
                instance->byteIOIndex = 0;
            }
            unsigned int partialBlock = (unsigned int)(dataByteLen - i);
            if (partialBlock + instance->byteIOIndex > K12_rateInBytes)
            {
                partialBlock = K12_rateInBytes - instance->byteIOIndex;
            }
            i += partialBlock;

            KeccakP1600_ExtractBytes(instance->state, curData, instance->byteIOIndex, partialBlock);
            curData += partialBlock;
            instance->byteIOIndex += partialBlock;
        }
    }
}

inline static void KangarooTwelve_Update(KangarooTwelve_Instance* ktInstance, unsigned char* input, unsigned long long inputByteLen)
{
    if (!ktInstance->blockNumber)
    {
        unsigned int len = (inputByteLen < (K12_chunkSize - ktInstance->queueAbsorbedLen)) ? (unsigned int)inputByteLen : (K12_chunkSize - ktInstance->queueAbsorbedLen);
        KangarooTwelve_F_Absorb(&ktInstance->finalNode, input, len);
        input += len;
        inputByteLen -= len;
        ktInstance->queueAbsorbedLen += len;
        if ((ktInstance->queueAbsorbedLen == K12_chunkSize) && inputByteLen)
        {
            unsigned char padding = 0x03;
            ktInstance->queueAbsorbedLen = 0;
            ktInstance->blockNumber = 1;
            KangarooTwelve_F_Absorb(&ktInstance->finalNode, &padding, 1);
            ktInstance->finalNode.byteIOIndex = (ktInstance->finalNode.byteIOIndex + 7) & ~7;
        }
    }
    else
    {
        if (ktInstance->queueAbsorbedLen)
        {
            unsigned int len = (inputByteLen < (K12_chunkSize - ktInstance->queueAbsorbedLen)) ? (unsigned int)inputByteLen : (K12_chunkSize - ktInstance->queueAbsorbedLen);
            KangarooTwelve_F_Absorb(&ktInstance->queueNode, input, len);
            input += len;
            inputByteLen -= len;
            ktInstance->queueAbsorbedLen += len;
            if (ktInstance->queueAbsorbedLen == K12_chunkSize)
            {
                unsigned char intermediate[K12_capacityInBytes];
                ktInstance->queueAbsorbedLen = 0;
                ++ktInstance->blockNumber;
                KangarooTwelve_F_AbsorbLastFewBits(&ktInstance->queueNode, K12_suffixLeaf);
                KangarooTwelve_F_Squeeze(&ktInstance->queueNode, intermediate, K12_capacityInBytes);
                KangarooTwelve_F_Absorb(&ktInstance->finalNode, intermediate, K12_capacityInBytes);
            }
        }
    }

    while (inputByteLen > 0)
    {
        unsigned int len = (inputByteLen < K12_chunkSize) ? (unsigned int)inputByteLen : K12_chunkSize;
        memset(&ktInstance->queueNode, 0, sizeof(KangarooTwelve_F));
        KangarooTwelve_F_Absorb(&ktInstance->queueNode, input, len);
        input += len;
        inputByteLen -= len;
        if (len == K12_chunkSize)
        {
            unsigned char intermediate[K12_capacityInBytes];
            ++ktInstance->blockNumber;
            KangarooTwelve_F_AbsorbLastFewBits(&ktInstance->queueNode, K12_suffixLeaf);
            KangarooTwelve_F_Squeeze(&ktInstance->queueNode, intermediate, K12_capacityInBytes);
            KangarooTwelve_F_Absorb(&ktInstance->finalNode, intermediate, K12_capacityInBytes);
        }
        else
        {
            ktInstance->queueAbsorbedLen = len;
        }
    }
}

inline static void KangarooTwelve(unsigned char* input, unsigned long long inputByteLen, unsigned char* output, unsigned long long outputByteLen)
{
    KangarooTwelve_Instance ktInstance;

    ktInstance.queueAbsorbedLen = 0;
    ktInstance.blockNumber = 0;
    memset(&ktInstance.finalNode, 0, sizeof(KangarooTwelve_F));

    KangarooTwelve_Update(&ktInstance, input, inputByteLen);

    unsigned char encbuf[sizeof(unsigned long long) + 1 + 2];

    encbuf[0] = 0;
    KangarooTwelve_Update(&ktInstance, encbuf, 1);

    unsigned char padding;
    if (!ktInstance.blockNumber)
    {
        padding = 0x07;
    }
    else
    {
        if (ktInstance.queueAbsorbedLen)
        {
            unsigned char intermediate[K12_capacityInBytes];
            ++ktInstance.blockNumber;
            KangarooTwelve_F_AbsorbLastFewBits(&ktInstance.queueNode, K12_suffixLeaf);
            KangarooTwelve_F_Squeeze(&ktInstance.queueNode, intermediate, K12_capacityInBytes);
            KangarooTwelve_F_Absorb(&ktInstance.finalNode, intermediate, K12_capacityInBytes);
        }
        --ktInstance.blockNumber;
        unsigned int n = 0;
        for (unsigned long long v = ktInstance.blockNumber; v && (n < sizeof(unsigned long long)); ++n, v >>= 8)
        {
        }
        for (unsigned int i = 1; i <= n; ++i)
        {
            encbuf[i - 1] = (unsigned char)(ktInstance.blockNumber >> (8 * (n - i)));
        }
        encbuf[n] = (unsigned char)n;
        encbuf[++n] = 0xFF;
        encbuf[++n] = 0xFF;
        KangarooTwelve_F_Absorb(&ktInstance.finalNode, encbuf, ++n);
        padding = 0x06;
    }
    KangarooTwelve_F_AbsorbLastFewBits(&ktInstance.finalNode, padding);
    KangarooTwelve_F_Squeeze(&ktInstance.finalNode, output, outputByteLen);
}