#pragma once


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

#include <cstring>
#include <stdint.h>

#include "TCPacketDef.h"

enum class EAudioSection { firsthalf, secondhalf, all };

class CTranscoderPacket
{
public:
	// constructor
	CTranscoderPacket(const STCPacket &tcp);

	// this packet's refector module;
	char GetModule() const;

	// codec
	const uint8_t *GetDStarData();
	const uint8_t *GetDMRData();
	const uint8_t *GetM17Data();
	void SetDStarData(const uint8_t *dstar);
	void SetDMRData(const uint8_t *dmr);
	void SetM17Data(const uint8_t *m17);

	// audio
	int16_t *GetAudio();

	// state of packet
	ECodecType GetCodecIn() const;
	uint16_t GetStreamId() const;
	bool IsLast() const;
	bool IsSecond() const;
	bool DStarIsSet() const;
	bool DMRIsSet() const;
	bool M17IsSet() const;
	bool AllCodecsAreSet() const;

private:
	STCPacket tcpacket;
	int16_t audio[160];
	bool dstar_set, dmr_set, m17_set;
};