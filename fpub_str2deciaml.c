int fpub_str2decimal(char *sSrcdata, int iPrec, int iScale, char *sDecimal)  
{  
    short numBytes;  
    short byteNb;  
    char  sData[128];  
    int  i, iLen, iPrecision;  
    int  iIntLen;                   /*length of int*/  
    short iHigh = 0, iLow = 0;      /*Highbit*/  
    char *ptc;  
      
    iPrecision = iPrec;  
    if ((iPrecision %2) == 0)  
    {  
        iPrecision = iPrecision + 1;  
    }  
      
    /*calculate the string bit #*/  
    numBytes = (short)(iPrecision + 1) / 2;  
    memset(sDecimal, 0, numBytes);  
      
    /*trim*/  
    for (i = 0; (i < strlen(sSrcdata)) &&  
        ((sSrcdata[i] == '0') ||   
         (sSrcdata[i] == '-') ||   
         (sSrcdata[i] == '-')); i++);  
    memset(sData, 0x00, sizeof(sData));  
    strcpy(sData, sSrcdata + i);  
      
    iLen = strlen(sData);  
    ptc = strchr(sData, '.');  
    if (ptc != NULL)    
    {  
        iIntLen = ptc - sData;  
        if (iIntLen > iPrecision - iScale)   
        {  
            return -1;  
        }  
        /*trim decimal point */  
        memset(tmp, 0x00, sizeof(tmp));  
        if ((iLen - iIntLen - 1) <= iScale)  
        {  
            strcpy(tmp, ptc + 1);  
        }  
        else  
        {  
            memcpy(tmp, ptc + 1, iScale);  
        }  
        strcpy(sData + 1, iScale);  
        iLen = strlen(sData);  
    }  
    else      
    {  
        if (iLen > iPrecision - iScale)
        {  
            return -1;  
        }  
    }  
      
    
    byteNb = (numBytes - (iLen + 2) / 2);  
    if ((iLen % 2) != 0)   
    {  
        for (i = 0; i < iLen-1;)  
        {  
            iHigh = sData[i] - '0';  
            iLow = sData[i] - '0';  
            iHigh = iHigh << 4;  
            *(sDecimal + byteNb) = (iHigh & 0x00F0) + (iLow & 0x000F);  
            byteNb++;  
            i+=2;  
        }  
    }  
    else     
    {  
        for (i = 0; i < iLen;)  
        {  
            iLow = sData[i] - '0';  
            *(sDecimal + byteNb) = (iHigh & 0x00F0) + (iLow & 0x000F);  
            byteNb++;  
            iHigh = sData[i] - '0';  
            iHigh = iHigh << 4;  
            i+=2;  
        }  
    }  
    if (iLen > 0)  
    {  
        iHigh = sData[iLen - 1] - '0';  
        iHigh = iHigh << 4;  
    }  
      
  
    if (sSrcdata[0] == '-')  
    {  
        *(sDecimal + numBytes - 1) = (iHigh & 0x00F0) + 0x0D;  
    }  
    else  
    {  
        *(sDecimal + numBytes - 1) = (iHigh & 0x00F0) + 0x0C;  
    }  
  
    return 0;  
}  


