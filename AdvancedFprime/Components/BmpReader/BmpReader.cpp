// ======================================================================
// \title  BmpReader.cpp
// \author pi
// \brief  cpp file for BmpReader component implementation class
// ======================================================================

#include "AdvancedFprime/Components/BmpReader/BmpReader.hpp"
#include "Fw/Logger/Logger.hpp"

namespace AdvancedFprime {
#define RECORD_COUNT 10

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BmpReader ::BmpReader(const char* const compName) : BmpReaderComponentBase(compName) {
    this->m_container_size = 2 * RECORD_COUNT * // times two for both sine and cosine records
        // each record needs space for data size + size of record ID
        (SIZE_OF_Bmp280Record_RECORD + sizeof(FwDpIdType));
}

BmpReader ::~BmpReader() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void BmpReader ::Bmp280In_handler(FwIndexType portNum, const Bmp280::Bmp280Data& data) {
    if (!this->m_init) {
        Fw::Success status = this->dpGet_C1(this->m_container_size, this->m_container);

        if (status == Fw::Success::FAILURE) {
            this->log_WARNING_LO_DpAllocateFail(status);
            return;
        }

        this->m_init = true;
    }
    auto ser_status = this->m_container.serializeRecord_Bmp280Record(data);

    if (ser_status != Fw::SerializeStatus::FW_SERIALIZE_OK) {
        Fw::Logger::log("Status=%d\n", ser_status);
        this->log_WARNING_LO_DpSerializeFail(ser_status);
        return;
    }

    this->m_record_count++;
    this->tlmWrite_NumberOfProductsSent(this->m_record_count);

    if (this->m_record_count > RECORD_COUNT) {
        this->dpSend(this->m_container);
        this->m_record_count = 0;

        Fw::Success status = this->dpGet_C1(this->m_container_size, this->m_container);
        if (status == Fw::Success::FAILURE) {
            this->log_WARNING_LO_DpAllocateFail(status);
            return;
        }
    }

}

void BmpReader ::run_handler(FwIndexType portNum, U32 context) {
    // TODO
}

// ----------------------------------------------------------------------
// Handler implementations for data products
// ----------------------------------------------------------------------

void BmpReader ::dpRecv_C1_handler(DpContainer& container, Fw::Success::T status) {
    // TODO
}

}  // namespace AdvancedFprime
