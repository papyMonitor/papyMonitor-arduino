-- Lua configuration file
-- Characters following "--" are always comment
-- It's important to respect the punctuation
-- Notably the {} and ,
-- There are three kind of fieds:

-- cfg:Default({
--     ...
-- })

-- cfg:Variable({
--     ...
-- })

-- cfg:Solid({
--     ...
-- })

-- cfg:Default contains the initialization
-- and rendering parameters

-- Each cfg:Variable contains information
-- About a variable to be reported
-- The mandatory fields are Name, Index and Type
-- *The Index is the same as the variable index in
--              the table variables[] of the skech
-- *The Type is the variable type to be reported
-- *The Name is a name to be displayed


--TYPES USED BY SERIAL MONITOR
--  typecfg enum {
--	eComDataType_Float		= 'f',
--	eComDataType_U32 		= 'W',
--	eComDataType_I32 		= 'w',
--	eComDataType_U16 		= 'I',
--	eComDataType_I16 		= 'i',
--	eComDataType_U8 		= 'B',
--	eComDataType_I8 		= 'b',
--} eComDataType_t

---------------  CONFIGURATION ---------------------- 
-- Normally you'll need only to modify the Baudrate
-- and the Layout on the Default
----------------------------------------------------- 
cfg:Default({
    ----------------------
    -- Mandatory fields --
    ----------------------    
    Baudrate = 230400, -- Baudrate of the serial port 
                       -- used by the target

    -- Commands from monitor to target
    -- Do not modify uykwyd (unless you know what you do)
    SetValue = '#',
    ReportValueOn = '?',
    ReportValueOff = '!',

    -- Messages from target to monitor
    -- Do not modify uykwyd
    IReportValue =        ':',
    IReportTextConsole =  '>',

    -- Every sampleTimeHW a variable is sent
    -- This value is usefull for the monitoring
    -- application in order to display the right timing
    -- Do not modify uykwyd
    SampleTimeHW= 0.001,

    --- LAYOUT
    --- On the upper side of the gui are the various
    --- Grouptabs. Each Grouptabs contains tabs
    --- that contain the monitored variables arranged
    --- in rows and colums. One can have several Grouptabs
    GroupTabs= { 
        {-- group0
            Tabs = {
                { -- Tab0
                    TabName="Arduino IO",
                    Columns= {
                        { 0, },
                        { 1, },
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
    Name="Outputs",
    Type="B",
    Index=0,
    Data= {
        { -- Data0
            BoolsOnU8 = true,
            BitsTexts = {
                "Not used", "Not used", "Out2", "Out3",
                "Out4", "Out5", "Out6", "Out7"
            },
            CanBitsEdits = {
                false,false,true,true,
                true,true,true,true
            },
        }
    }
})

cfg:Variable({
    Name="Inputs",
    Type="B",
    Index=1,
    Data= {
        { -- Data0
            BoolsOnU8 = true,
            BitsTexts = {
                "Pin8", "Pin9", "Pin10", "Pin11",
                "Pin12", "Pin13", "Not used", "Not used"
            },
        }
    }
})


