#pragma once
#include <AudioClient.h>
#include <mmdeviceapi.h>
#include "ISoundSource.h"
#include "AsyncCallback.h"

namespace BeatBuilder
{
	namespace Audio
	{
		public ref class AudioRenderer sealed
		{
		public:
			static Windows::Foundation::IAsyncOperation<AudioRenderer^>^ CreateAsync();

			void Start();
			void Stop();

			virtual ~AudioRenderer();

		internal:
			void AddSoundSource(std::shared_ptr<ISoundSource> source);

		private:
			Microsoft::WRL::ComPtr<IAudioClient2> m_audioClient;
			Microsoft::WRL::ComPtr<IAudioRenderClient> m_audioRenderClient;
			WAVEFORMATEX* m_mixFormat;
			UINT32 m_bufferSize;
			bool m_isTurnedOn;
			std::shared_ptr<ISoundSource> m_soundSource;
			DWORD m_proAudioWorkQueueId;

			// MF Callback
			HRESULT OnRenderCallback(IMFAsyncResult* result); 
			AsyncCallback<AudioRenderer> m_renderCallback;
			HANDLE m_renderCallbackEvent;
			ComPtr<IMFAsyncResult> m_renderCallbackResult;
			MFWORKITEM_KEY m_renderCallbackKey;
			CRITICAL_SECTION m_renderCallbackCS;

			AudioRenderer(Microsoft::WRL::ComPtr<IAudioClient2> renderClient);
			void Initialize();
			void InitializeWasapi();
			void InitializeMediaFoundation();
		};
	}
}
