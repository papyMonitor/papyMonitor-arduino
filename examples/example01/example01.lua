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
                    TabName="Example",
                    Columns= {
                        { 0, },
                        { 1 },
                    }
                },
            },
        },
    },
    Plot=true,
})

---------------
cfg:Variable({
    Name="My float",
    Type= "f",
    Index= 0,
    Data = {
        {
            CanPlot=true,
        }
    }
})

---------------
cfg:Variable({
    Name="My byte",
    Type= "B",
    Index= 1,
    Data = {
        {
            CanPlot=true,
        }
    }   
})


