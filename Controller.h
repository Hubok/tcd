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

#include <vector>
#include <set>
#include <memory>
#include <atomic>
#include <future>

#include "PacketQueue.h"
#include "DV3003.h"
#include "configure.h"
#include "UnixDgramSocket.h"

// local audio storage
class CAudioBlock
{
public:
    int16_t   operator [](int i) const {return audio[i];}
    int16_t & operator [](int i)       {return audio[i];}
	int16_t  *data() { return audio; }
	const int16_t  *cdata() const { return audio; }
protected:
	int16_t audio[160];
};

class CController
{
public:
	CController() : dmr_vocoder_count(0), current_dmr_vocoder(0), dstar_vocoder_count(0), current_dstar_vocoder(0), keep_running(true) {}
	bool Start();
	void Stop();
	bool IsRunning() { return keep_running; }

protected:
	unsigned int dmr_vocoder_count, current_dmr_vocoder, dstar_vocoder_count, current_dstar_vocoder;
	std::atomic<bool> keep_running;
	std::future<void> reflectorThread, ambeThread;
	std::vector<std::shared_ptr<CDV3003>> dmr_device, dstar_device;
	CUnixDgramReader reader;
	CUnixDgramWriter writer;
	std::vector<CAudioBlock> dmr_audio_block, dstar_audio_block;
	std::vector<CPacketQueue> dmr_packet_queue, dstar_packet_queue;

	bool InitDevices();
	void IncrementDMRVocoder(void);
	void IncrementDStarVocoder(void);
	// processing threads
	void ReadReflector();
	void ReadAmbeDevices();

	void CSVtoSet(const std::string &str, std::set<std::string> &set, const std::string &delimiters = ",");
};
