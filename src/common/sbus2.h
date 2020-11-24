#include <mbed.h>

/**
 * @code
 * Sbus2Receiver sbus2(PC_10, PC_11);
 * 
 * if(sbus2.checkUpdate()){
 *  printf("%04u, %04u\n", sbus2.getCh(0), sbus2.getCh(1));
 * }
 * if(sbus2.checkLost()){
 *  printf("sbus2 lost\n");
 * }
 */

#define SBUS2_BYTE_SIZE 24
#define SBUS2_CH_SIZE 16

class Sbus2Receiver {
public:
    Sbus2Receiver(PinName tx_pin, PinName rx_pin);
    bool checkUpdate();
    bool checkLost();
    unsigned int getCh(int channel);

private:
    void rxCallback(void);
    int decodeCh(int offset_byte, int offset_bit);

    RawSerial serial_;
    int index_{-1};
    unsigned char buffer_[SBUS2_BYTE_SIZE];
    int output_[SBUS2_CH_SIZE];
    bool valid_{false};
    bool lost_{false};
};

Sbus2Receiver::Sbus2Receiver(PinName tx_pin, PinName rx_pin)
    : serial_(tx_pin, rx_pin, 100000)
{
    serial_.attach(this, &Sbus2Receiver::rxCallback);
}

void Sbus2Receiver::rxCallback(void)
{
    char recv = serial_.getc();
    if (index_ == -1) {
        if (recv == 0x0f) {
            index_ = 0;
        }
    } else {
        buffer_[index_] = recv;
        index_++;
    }

    if (index_ == 24) {
        index_ = -1;
        bool valid = !(buffer_[22] & 0x04);
        bool lost = !!(buffer_[22] & 0x08);
        if (valid) {
            for (int i = 0; i < SBUS2_CH_SIZE; i++) {
                int offset_byte = (i * 11) / 8;
                int offset_bit = (i * 11) % 8;
                output_[i] = decodeCh(offset_byte, offset_bit);
            }
        }
        valid_ = valid;
        lost_ = lost;
    }
}

int Sbus2Receiver::decodeCh(int offset_byte, int offset_bit)
{
    if (offset_bit < 5) {
        unsigned int l_byte = buffer_[offset_byte] >> offset_bit;
        unsigned int h_byte = buffer_[offset_byte + 1] << (8 - offset_bit);
        return (h_byte | l_byte) & 0x7ff;
    } else {
        unsigned int l_byte = buffer_[offset_byte] >> offset_bit;
        unsigned int m_byte = buffer_[offset_byte + 1] << (8 - offset_bit);
        unsigned int h_byte = buffer_[offset_byte + 2] << (16 - offset_bit);
        return (h_byte | m_byte | l_byte) & 0x7ff;
    }
}

bool Sbus2Receiver::checkUpdate()
{
    bool output = valid_;
    valid_ = false;
    return output;
}

bool Sbus2Receiver::checkLost()
{
    bool output = lost_;
    lost_ = false;
    return output;
}

unsigned int Sbus2Receiver::getCh(int channel)
{
    unsigned int output = 1024;
    if (0 <= channel && channel < SBUS2_CH_SIZE) {
        output = output_[channel];
    }
    return output;
}
