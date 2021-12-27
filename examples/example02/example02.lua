-- Lua configuration file
-- See "The User Configuration File (UCF)"" documentation

cfg:Default({  
    Baudrate = 230400,
    SetValue = '#',
    ReportValueOn = '?',
    ReportValueOff = '!',
    IReportValue =        ':',
    IReportTextConsole =  '>',
    SampleTimeHW= 0.001,
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
    Plot=true,
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


