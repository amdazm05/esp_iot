idf_component_register(
                    SRCS 
                            "./src/softapwificonfiguration.cc"
                            "./src/httpserver.cc"
                            "./src/stawifimode.cc"
                            "./src/sensorscheduler.cc"
                            "./src/storagenvshandler.cc"
                        #     Utility
                            "./utils/uri/uriutility.cc"  
                        #     Sensor Library imports
                            "./sensors/bme680/bme680.c"
                            "./sensors/bme680/bme680_platform.c"
                            "./sensors/bme680/esp8266_wrapper.c"
                        #     main
                            "main.cc" 
                    INCLUDE_DIRS 
                            "." 
                            "./includes"
                            "./sensors/bme680"
                            "./html"
                            "./utils"
                            "./env"
                        )
