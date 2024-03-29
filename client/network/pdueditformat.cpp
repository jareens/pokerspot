/****************************************************************************

  Copyright (c) PokerSpot International, 1999

  Title    : class PDUEditFormat
  Created  : 08/25/2000

  OVERVIEW : 

 ****************************************************************************/

#include "stdafx.h"
#include "network/pdueditformat.h"
#include "base/gamelogic.h"
#ifndef PSPOT_TABLE_MODULE_
#include "loungedlg/resource.h"
#include "loungedlg/editordlg.h"
#endif


BEGIN_NAMESPACE(Network)

USING_NS_T(Base, GameLogic);

PDUEditFormat::PDUEditFormat(const char* buf)
    :
    PDUHeader(buf),
    flags_   (0)
{
    u_int16_t* pint = (u_int16_t*)&buf[PDU_HEADER_SIZE];
    flags_ = ntohs(*pint++);

    int datalength = length_ - PDU_HEADER_SIZE - sizeof(u_int16_t);
    if (datalength > 0)
    {
        data_ = new char[datalength + 1];
        if (data_)
        {
            memcpy(data_, (u_byte_t*)buf, datalength);
            data_[datalength] = '\0';
        }
    }
}


PDUEditFormat::~PDUEditFormat()
{
    if (data_ != NULL)
    {
        delete [] data_;
        data_ = NULL;
    }
}

void PDUEditRules::execute(GameState* pS)
{
#ifndef PSPOT_TABLE_MODULE_
    if (CEditorDlg::Inst())
    {
        CEditorDlg::Inst()->setText(data_);
        delete [] data_;
        data_ = NULL;
    }
#endif
}


END_NAMESPACE(Network)

