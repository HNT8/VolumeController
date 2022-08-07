#include <Windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

bool success = false;
float Volume = 0;

extern "C" bool SetVolume(int vol) {
	HRESULT hr = CoInitialize(NULL);
	if (hr == S_OK) {
		IMMDeviceEnumerator* pIMMDeviceEnumerator = NULL;
		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID*)&pIMMDeviceEnumerator);

		if (hr == S_OK) {
			IMMDevice* defaultDevice = NULL;
			hr = pIMMDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
			pIMMDeviceEnumerator->Release();
			pIMMDeviceEnumerator = NULL;

			if (hr == S_OK) {
				IAudioEndpointVolume* EndPointVolume = NULL;
				hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (LPVOID*)&EndPointVolume);
				defaultDevice->Release();

				float Volume = vol / 100;
				hr = EndPointVolume->SetMasterVolumeLevelScalar(Volume, NULL);
				if (hr == S_OK) success = true;

				EndPointVolume->Release();
				EndPointVolume = NULL;
			}

			CoUninitialize();
		}
	}

	return success;
}

extern "C" int GetVolume() {
	HRESULT hr = CoInitialize(NULL);
	if (hr == S_OK) {
		IMMDeviceEnumerator* pIMMDeviceEnumerator = NULL;
		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID*)&pIMMDeviceEnumerator);

		if (hr == S_OK) {
			IMMDevice* defaultDevice = NULL;
			hr = pIMMDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
			pIMMDeviceEnumerator->Release();
			pIMMDeviceEnumerator = NULL;

			if (hr == S_OK) {
				IAudioEndpointVolume* EndPointVolume = NULL;
				hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (LPVOID*)&EndPointVolume);
				defaultDevice->Release();

				
				hr = EndPointVolume->GetMasterVolumeLevelScalar(&Volume);
				if (hr == S_OK) success = true;

				EndPointVolume->Release();
				EndPointVolume = NULL;
			}
			CoUninitialize();
		}
	}

	return (int)(Volume * 100);
}