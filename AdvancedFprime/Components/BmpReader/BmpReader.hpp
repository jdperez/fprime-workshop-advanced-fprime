// ======================================================================
// \title  BmpReader.hpp
// \author pi
// \brief  hpp file for BmpReader component implementation class
// ======================================================================

#ifndef AdvancedFprime_BmpReader_HPP
#define AdvancedFprime_BmpReader_HPP

#include "AdvancedFprime/Components/BmpReader/BmpReaderComponentAc.hpp"

namespace AdvancedFprime {

class BmpReader final : public BmpReaderComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct BmpReader object
    BmpReader(const char* const compName  //!< The component name
    );

    //! Destroy BmpReader object
    ~BmpReader();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for Bmp280In
    void Bmp280In_handler(FwIndexType portNum,  //!< The port number
                          const Bmp280::Bmp280Data& data) override;

    //! Handler implementation for run
    void run_handler(FwIndexType portNum,  //!< The port number
                     U32 context           //!< The call order
                     ) override;

  private:
    DpContainer m_container;
    U32 m_container_size{0};
    U32 m_record_count{0};
    bool m_init{false};

    // ----------------------------------------------------------------------
    // Handler implementations for data products
    // ----------------------------------------------------------------------

    //! Receive a container of type C1
    void dpRecv_C1_handler(DpContainer& container,  //!< The container
                           Fw::Success::T status    //!< The container status
                           ) override;
};

}  // namespace AdvancedFprime

#endif
