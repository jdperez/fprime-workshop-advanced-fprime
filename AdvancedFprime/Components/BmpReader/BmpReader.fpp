module AdvancedFprime {
    @ Component for reading in BMP280 data
    active component BmpReader {
        @ Number of Data Products sent
        telemetry NumberOfProductsSent: U64

        @ Record for handling BMP280 data
        product record Bmp280Record: Bmp280.Bmp280Data id 0x00

        product container C1 default priority 10

        # @ Example port: receiving calls from the rate group
        sync input port run: Svc.Sched

        async input port Bmp280In: Bmp280.Bmp280DataOut

        event DpAllocateFail(status: Fw.Success) severity warning low id 0 format "Failed to allocate DP container: {}"
        event DpSerializeFail(status: bool) severity warning low id 1 format "Failed to serialize: {}"


        ##############################################################################
        #### Uncomment the following examples to start customizing your component ####
        ##############################################################################

        # @ Example async command
        # async command COMMAND_NAME(param_name: U32)


        # @ Example event
        # event ExampleStateEvent(example_state: Fw.On) severity activity high id 0 format "State set to {}"

        # @ Example parameter
        # param PARAMETER_NAME: U32

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending command registrations
        command reg port cmdRegOut

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

        product get port productGetOut
        product request port productRequestOut
        async product recv port productRecvIn
        product send port productSendOut
    }
}