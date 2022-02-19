#include <stdio.h>
#include <windows.h>

#pragma comment(lib, "winmm.lib")

HMIDIOUT hMidiOut_NordModular;
HMIDIOUT hMidiOut_MicroFreak;
HMIDIOUT hMidiOut_Prophet;
HMIDIOUT hMidiOut_Iridium;
HMIDIOUT hMidiOut_JX3P;
HMIDIIN hMidiIn;

//int get_input_MidiDevices() {
//	MIDIINCAPS caps;
//	unsigned dev_in;
//	unsigned int nMidiDeviceNum = midiInGetNumDevs();
//	printf("  Midi Input  Devices:\n");
//	if (nMidiDeviceNum > 1) {
//		for (unsigned int i = 0; i < nMidiDeviceNum; ++i) {
//			midiInGetDevCaps(i, &caps, sizeof(MIDIINCAPS));
//			printf("  [%2i] %s\n", i, caps.szPname);
//		}
//		printf("  Select Midi Input: ");
//		scanf_s("%i", &dev_in);
//	}
//	else {
//		fprintf(stderr, "  no Midi-IN Device");
//		return -1;
//	}
//	return dev_in;
//}
//
//int get_output_MidiDevices() {
//	MIDIOUTCAPS caps;
//	unsigned int dev_out;
//	unsigned int nMidiDeviceNum = midiOutGetNumDevs();
//	printf("  Midi Output Devices:\n");
//	if (nMidiDeviceNum > 1) {
//		for (unsigned int i = 0; i < nMidiDeviceNum; ++i) {
//			midiOutGetDevCaps(i, &caps, sizeof(MIDIOUTCAPS));
//			printf("  [%2i] %s\n", i, caps.szPname);
//		}
//		printf("  Select Midi Output: ");
//		scanf_s("%d", &dev_out);
//	}
//	else {
//		fprintf(stderr, "  midiOutGetNumDevs() return 0...");
//		return -1;
//	}
//	return dev_out;
//}

#define MIDITRAC 8

#define NORDMODULAR 12
#define MICROFREAK 11
#define PROPHET 7
#define IRIDIUM 8
#define JX3P 10

void CALLBACK MidiInProc(HMIDIIN hmidiIN, unsigned int wMsg, long dwInstance, unsigned int dwParam1, unsigned int dwParam2) {
	switch (dwParam1 & 0xf) {
		case 0: // MidiIputKanal 1 -> NordModular Slot 1 Kanal 1
			midiOutShortMsg(hMidiOut_NordModular, dwParam1);
			break;
		case 1: // MidiIputKanal 2 -> NordModular Slot 2 Kanal 2
			midiOutShortMsg(hMidiOut_NordModular, dwParam1);
			break;
		case 2: // MidiIputKanal 3 -> NordModular Slot 3 Kanal 3
			midiOutShortMsg(hMidiOut_NordModular, dwParam1);
			break;
		case 3: // MidiIputKanal 4 -> NordModular Slot 4 Kanal 4
			midiOutShortMsg(hMidiOut_NordModular, dwParam1);
			break;
		case 4: // MidiIputKanal 5 -> JX3P (all Channels)
			midiOutShortMsg(hMidiOut_JX3P, dwParam1);
			break;
		case 5: // MidiIputKanal 6 -> MicroFreak Kanal 1
			dwParam1 -= 5;
			midiOutShortMsg(hMidiOut_MicroFreak, dwParam1);
			break;
		case 6: // MidiIputKanal 7 -> Prophet Kanal 1
			dwParam1 -= 6;
			midiOutShortMsg(hMidiOut_Prophet, dwParam1);
			break;
		case 7: // MidiIputKanal 8 -> Iridium Layer 1 Kanal 1
			dwParam1 -= 7;
			midiOutShortMsg(hMidiOut_Iridium, dwParam1);
			break;
		case 8: // MidiIputKanal 9 -> Iridium Layer 2 Kanal 2
			dwParam1 -= 7;
			midiOutShortMsg(hMidiOut_Iridium, dwParam1);
			break;
		case 9:
			break;
		case 10:
			break;
		case 11:
			break;
		case 12:
			break;
		case 13:
			break;
		case 14:
			break;
		case 15:
			break;
		default:
			break;
	}
}

int main() {
	midiOutOpen(&hMidiOut_NordModular, NORDMODULAR, 0, 0, 0);
	midiOutOpen(&hMidiOut_MicroFreak, MICROFREAK, 0, 0, 0);
	midiOutOpen(&hMidiOut_Prophet, PROPHET, 0, 0, 0);
	midiOutOpen(&hMidiOut_Iridium, IRIDIUM, 0, 0, 0);
	midiOutOpen(&hMidiOut_JX3P, JX3P, 0, 0, 0);
	midiInOpen(&hMidiIn, MIDITRAC, (DWORD_PTR)(void*)MidiInProc, 0, CALLBACK_FUNCTION);
	midiInStart(hMidiIn);
	printf("Route666 by @liceD25...\n\nNordModular:\t1|2|3|4\nRoland JX3P:\t5\nMicroFreak:\t6\nProphet:\t7\nIridium:\t8|9\n\n[ESC]");
	while (!(GetAsyncKeyState(VK_ESCAPE) &0x8000)){}
	midiInStop(hMidiIn);
	midiOutReset(hMidiOut_NordModular);
	midiOutReset(hMidiOut_MicroFreak);
	midiOutReset(hMidiOut_Prophet);
	midiOutReset(hMidiOut_Iridium);
	midiOutReset(hMidiOut_JX3P);
	return 0;
}
