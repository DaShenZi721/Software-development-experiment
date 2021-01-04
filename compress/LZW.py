# coding: utf-8
import sys

def LZW(inStr, narrow=False, bits=14):
    '''使用LZW压缩算法压缩。
        narrow为True时输出字节流位紧缩
        默认最大位宽14位，允许范围12~16位'''
    if isinstance(inStr, str):
        inStr = list(inStr)
        for i in range(len(inStr)):
            inStr[i] = ord(inStr[i])
    sOutStr = [256]  # 先放一个 开始&清除 标记
    mTagMap = {}  # 字典
    iTagCurrent = 258  # 当前的标记总数 0~255 标记256 为begin & clear , 257 为end
    iBitsLen = 9

    iTag = inStr[0]  # 当前标记
    ii = 0
    cTemp = 0
    if bits > 16 or bits < 12:
        return None
    iMaxLen = (1 << bits) - 1  # 最多允许的标记数，由位宽决定

    for ii in range(1, len(inStr)):
        cChar = inStr[ii]
        cTemp = (iTag << 8) + cChar  # （前缀 后缀）
        if cTemp in mTagMap:  # 该（前缀 后缀）已存在
            iTag = mTagMap[cTemp]  # 取出其标记
        else:  # 不存在
            sOutStr.append(iTag)  # 将前缀放入输出流
            mTagMap[cTemp] = iTagCurrent
            iTagCurrent += 1  # 增加一个标记，并放入字典
            iTag = cChar  # 当前标记为后缀

        if iTagCurrent >= iMaxLen:  # 如果到达了最大标记数，清除字典，从头开始
            sOutStr.append(256)
            mTagMap = {}
            iTagCurrent = 258

    if iTag != 0:
        sOutStr.append(iTag)
    sOutStr.append(257)  # 放入结束标记

    if narrow:  # 位紧缩
        return Narrow(sOutStr)
    else:
        return sOutStr


def Narrow(sOutStr):
    sOutN = []
    iTemp = 0
    BitLeft = 0
    nowBit = 9  # 当前位宽
    nowStag = 1 << nowBit  # 当前位宽允许的标记数
    nowTagCount = 258
    for cChar in sOutStr:
        iTemp = iTemp + (cChar << BitLeft)
        nowTagCount += 1
        BitLeft += nowBit

        if cChar == 256:
            nowBit = 9
            nowStag = 1 << nowBit
            nowTagCount = 258

        if nowTagCount >= nowStag:
            nowBit += 1
            nowStag = 1 << nowBit

        while BitLeft >= 8:
            sOutN.append(iTemp & 0xff)
            iTemp = iTemp >> 8
            BitLeft -= 8
    if BitLeft > 0:
        sOutN.append(iTemp)
    return sOutN


def UnNarrow(inStr):
    sOut = []
    iTemp = 0
    BitLeft = 0
    nowBit = 9
    nowStag = 1 << nowBit
    mask = nowStag - 1
    nowTagCount = 258
    for cChar in inStr:
        iTemp = iTemp + (cChar << BitLeft)
        BitLeft += 8
        if BitLeft >= nowBit:
            cTemp = iTemp & mask
            iTemp = iTemp >> nowBit
            BitLeft -= nowBit
            sOut.append(cTemp)
            nowTagCount += 1
            if nowTagCount >= nowStag:
                nowBit += 1
                nowStag = 1 << nowBit
                mask = nowStag - 1
            if cTemp == 256:
                nowBit = 9
                nowStag = 1 << nowBit
                mask = nowStag - 1
                nowTagCount = 258
    if BitLeft > 0:
        sOut.append(iTemp)

    return sOut


def deTag(mTagMap, nowTag, outStr):
    '''将一个标记转化为元字符序列，并放入到输出流中'''
    if nowTag >= 0:
        sTemp = []
        while nowTag > 255:
            pair = mTagMap[nowTag]
            sTemp.append(pair[1])
            nowTag = pair[0]
        sTemp.append(nowTag)
        sTemp.reverse()
        outStr += sTemp
    return nowTag


def UnLZW(inStr, narrow=False):
    if narrow:
        inStr = UnNarrow(inStr)

    mTagMap = {}
    outStr = []
    nowTagCount = 258
    sTemp = []
    nowTag = -1
    for cChar in inStr:
        if cChar == 256:
            if nowTag >= 0:
                deTag(mTagMap, nowTag, outStr)
            mTagMap = {}
            nowTagCount = 258
            nowTag = -1
        elif cChar == 257:
            if nowTag >= 0:
                deTag(mTagMap, nowTag, outStr)
                nowTag = -1
            return outStr
        elif nowTag == -1:  # 刚开始
            nowTag = cChar
        else:
            pair = [nowTag, 0]
            mTagMap[nowTagCount] = pair
            nowTagCount += 1
            surfix = cChar
            while surfix > 255:
                if surfix not in mTagMap:
                    print
                    'Thera are errors in input'
                    return outStr
                surfix = mTagMap[surfix][0]
            pair[1] = surfix
            deTag(mTagMap, nowTag, outStr)
            nowTag = cChar


def fileLZW(inFile, outFile, bit=14):
    import os
    fsize = os.stat(inFile)[6]
    f = os.open(inFile, 32768)
    # f = os.open(inFile, os.O_BINARY)
    s = os.read(f, fsize)
    os.close(f)

    a = LZW(s, True, bit)
    f = open(outFile, 'wb')
    outs = ''
    for i in a:
        outs += chr(i)
    f.write(outs)
    f.close()


def fileUnlzw(inFile, outFile):
    import os
    fsize = os.stat(inFile)[6]
    f = os.open(inFile, 32768)
    # f = os.open(inFile, os.O_BINARY)
    s = os.read(f, fsize)
    a = []
    for i in s:
        a.append(ord(i))
    b = UnLZW(a, True)
    f = open(outFile, 'wb')
    outs = ''
    for i in b:
        outs += chr(i)
    f.write(outs)
    f.close()

input=sys.argv[1]
output=sys.argv[2]
compress_or_decompress=sys.argv[3] # 1:compress 2:decompress
if compress_or_decompress=='1':
    fileLZW(input,output)
elif compress_or_decompress=='2':
    fileUnlzw(input,output)
else:
    print('Invalid input!')