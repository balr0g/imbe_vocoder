#include <cinttypes>

class imbe_vocoder_impl;
class imbe_vocoder
{
public:
    imbe_vocoder(void);	// constructor
    ~imbe_vocoder();   	// destructor
    // imbe_encode compresses 160 samples (in unsigned int format)
    // outputs u[] vectors as frame_vector[]
    void imbe_encode(int16_t *frame_vector, int16_t *snd);
    
    // imbe_decode decodes IMBE codewords (frame_vector),
    // outputs the resulting 160 audio samples (snd)
    void imbe_decode(int16_t *frame_vector, int16_t *snd);

private:
    imbe_vocoder_impl *Impl;
};
