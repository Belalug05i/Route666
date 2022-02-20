#include <stdio.h>
#include <windows.h>

#pragma comment(lib, "winmm.lib")

HMIDIIN hMidiIn_MidiTraC;

HMIDIOUT hMidiOut_NordModular;
HMIDIOUT hMidiOut_MicroFreak;
HMIDIOUT hMidiOut_Prophet;
HMIDIOUT hMidiOut_Iridium;
HMIDIOUT hMidiOut_JX3P;

#define MIDITRAC 8

#define NORDMODULAR 12
#define MICROFREAK 11
#define PROPHET 7
#define IRIDIUM 8
#define JX3P 10

//void show_MidiDevices() {
//	MIDIINCAPS inputCaps;
//	MIDIOUTCAPS outputCaps;
//	unsigned int inputDeviceNum = midiInGetNumDevs();
//	unsigned int outputDeviceNum = midiOutGetNumDevs();
//	printf("  Midi Input Devices:\n  -------------------\n");
//	if (inputDeviceNum > 0) {
//		for (unsigned int i = 0; i < inputDeviceNum; ++i) {
//			midiInGetDevCaps(i, &inputCaps, sizeof(MIDIINCAPS));
//			wprintf(L"  [%2i] %s\n", i, inputCaps.szPname);
//		}
//	}
//	else {
//		fprintf(stderr, "  no Midi-In Device");
//	}
//	printf("\n  Midi Output Devices:\n  --------------------\n");
//	if (outputDeviceNum > 0) {
//		for (unsigned int i = 0; i < outputDeviceNum; ++i) {
//			midiOutGetDevCaps(i, &outputCaps, sizeof(MIDIOUTCAPS));
//			wprintf(L"  [%2i] %s\n", i, outputCaps.szPname);
//		}
//	}
//	else {
//		fprintf(stderr, "  no Midi-Out Device");
//	}
//	printf("\n  press [SPACE]\n");
//	while (!(GetAsyncKeyState(VK_SPACE) & 0x8000)) {}
//}

void CALLBACK MidiInProc(HMIDIIN hmidiIN, unsigned int wMsg, long dwInstance, unsigned int dwParam1, unsigned int dwParam2) {
	if (dwParam1 == 0xf8) { // handle MidiClock
		midiOutShortMsg(hMidiOut_NordModular, 0xf8);
		midiOutShortMsg(hMidiOut_MicroFreak, 0xf8);
		midiOutShortMsg(hMidiOut_Prophet, 0xf8);
		midiOutShortMsg(hMidiOut_Iridium, 0xf8);
	} 
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
	//show_MidiDevices();
	//system("CLS");

	midiOutOpen(&hMidiOut_NordModular, NORDMODULAR, 0, 0, 0);
	midiOutOpen(&hMidiOut_MicroFreak, MICROFREAK, 0, 0, 0);
	midiOutOpen(&hMidiOut_Prophet, PROPHET, 0, 0, 0);
	midiOutOpen(&hMidiOut_Iridium, IRIDIUM, 0, 0, 0);
	midiOutOpen(&hMidiOut_JX3P, JX3P, 0, 0, 0);

	midiInOpen(&hMidiIn_MidiTraC, MIDITRAC, (DWORD_PTR)(void*)MidiInProc, 0, CALLBACK_FUNCTION);
	midiInStart(hMidiIn_MidiTraC);

	printf("Route666 by @liceD25...\n\nNordModular:\t1|2|3|4\nRoland JX3P:\t5\nMicroFreak:\t6\nProphet:\t7\nIridium:\t8|9\n\n[ESC]");
	while (!(GetAsyncKeyState(VK_ESCAPE) &0x8000)){}

	midiInStop(hMidiIn_MidiTraC);

	midiOutReset(hMidiOut_NordModular);
	midiOutReset(hMidiOut_MicroFreak);
	midiOutReset(hMidiOut_Prophet);
	midiOutReset(hMidiOut_Iridium);
	midiOutReset(hMidiOut_JX3P);
	return 0;
}
