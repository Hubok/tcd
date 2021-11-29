// tcd - a hybid transcoder using DVSI hardware and Codec2 software
// Copyright © 2021 Thomas A. Early N7TAE

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <iostream>

#include "TranscoderPacket.h"

CTranscoderPacket::CTranscoderPacket(const STCPacket &tcp) : dstar_set(false), dmr_set(false), m17_set(false)
{
	tcpacket.module = tcp.module;
	tcpacket.is_last = tcp.is_last;
	tcpacket.is_second = tcp.is_second;
	tcpacket.streamid = tcp.streamid;
	tcpacket.codec_in = tcp.codec_in;
	switch (tcp.codec_in)
	{
	case ECodecType::dstar:
		SetDStarData(tcp.dstar);
		break;
	case ECodecType::dmr:
		SetDMRData(tcp.dmr);
		break;
	case ECodecType::c2_1600:
	case ECodecType::c2_3200:
		SetM17Data(tcp.m17);
		break;
	default:
		std::cerr << "Trying to allocate CTranscoderPacket with an unknown codec type!" << std::endl;
		break;
	}
}

char CTranscoderPacket::GetModule() const
{
	return tcpacket.module;
}

const uint8_t *CTranscoderPacket::GetDStarData()
{
	return tcpacket.dstar;
}

const uint8_t *CTranscoderPacket::GetDMRData()
{
	return tcpacket.dmr;
}

const uint8_t *CTranscoderPacket::GetM17Data()
{
	return tcpacket.m17;
}

void CTranscoderPacket::SetDStarData(const uint8_t *dstar)
{
	memcpy(tcpacket.dstar, dstar, 9);
	dstar_set = true;
}
void CTranscoderPacket::SetDMRData(const uint8_t *dmr )
{
	memcpy(tcpacket.dmr, dmr, 9);
	dmr_set = true;
}

void CTranscoderPacket::SetM17Data(const uint8_t *m17)
{
	memcpy(tcpacket.m17, m17, 16);
	m17_set = true;
}

int16_t *CTranscoderPacket::GetAudio()
{
	return audio;
}

ECodecType CTranscoderPacket::GetCodecIn() const
{
	return tcpacket.codec_in;
}

uint16_t CTranscoderPacket::GetStreamId() const
{
	return tcpacket.streamid;
}

bool CTranscoderPacket::IsLast() const
{
	return tcpacket.is_last;
}

bool CTranscoderPacket::IsSecond() const
{
	return tcpacket.is_second;
}

bool CTranscoderPacket::DStarIsSet() const
{
	return dstar_set;
}

bool CTranscoderPacket::DMRIsSet() const
{
	return dmr_set;
}

bool CTranscoderPacket::M17IsSet() const
{
	return m17_set;
}

bool CTranscoderPacket::AllCodecsAreSet() const
{
	return (dstar_set && dmr_set && m17_set);
}