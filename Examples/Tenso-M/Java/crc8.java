short ucCrcMaker(short[] InputData) {
       
    short Pollinom = 0x69;
    short CrcCode = 0x00;
            
    for(int i = 0; i < InputData.length; i++) {
        short Data = (short) (InputData[i]);
        for (int j = 0; j < 8; j++) {
            if((CrcCode & (1 << 7)) > 0) {
                CrcCode *= 2;
                if((Data & (1 << 7)) > 0) CrcCode++;
                CrcCode ^= Pollinom;
            }
            else {
                CrcCode *= 2;
                if((Data & (1 << 7)) > 0) CrcCode++;
            }
                Data *= 2;
        }     
    }
        return (short) (CrcCode & 0xFF);
}
