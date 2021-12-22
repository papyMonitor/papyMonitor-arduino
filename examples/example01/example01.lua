--TYPES USED BY SERIAL MONITOR
--typecfg enum {
--	eComDataType_Float		= 'f', -- 8 chars
--	eComDataType_U32 		= 'W', -- 8 chars
--	eComDataType_I32 		= 'w', -- 8 chars
--	eComDataType_U16 		= 'I', -- 4 chars
--	eComDataType_I16 		= 'i', -- 4 chars
--	eComDataType_U8 		= 'B', -- 2 chars
--	eComDataType_I8 		= 'b', -- 2 chars
--} eComDataType_t--

---------------  CONFIGURATION ---------------------- 
cfg:Default({
    ----------------------
    -- Mandatory fields --
    ----------------------    
    Baudrate = 230400,

    -- Commands from monitor to target;
    SetValue = '#',
    ReportValueOn = '?',
    ReportValueOff = '!',

    -- Messages from target to monitor
    IReportValue =        ':',
    IReportTextConsole =  '>',

    --Every sampleTimeHW a variable is sent
    SampleTimeHW= 0.001,

    --- LAYOUT
    GroupTabs= { 
        {-- group0
            Tabs = {
                { -- Tab0
                    TabName="Example",
                    Columns= {
                        { 0, },
                        { 1 }, -- variables indexes
                    }
                },
            },
        },
    },

    ----------------------
    -- Optional fields  --
    ---------------------- 
    Endian=     'little',   -- default = 'little'
    Vue3D=      false,       -- default = 'false'
    Plot=       true,       -- default = 'false'
})

---------------
cfg:Variable({
    Name="My float",
    Type= "f",
    Index= 0,
})

---------------
cfg:Variable({
    Name="My byte",
    Type= "B",
    Index= 1,
})


