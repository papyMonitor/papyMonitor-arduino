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
                    }
                },
            },
        },
    },

    Plot=true,
})

---------------
cfg:Variable({
    Name="Analog pins",
    Type="f",
    Index=0,
    Data= {
        { SingleText = "A0", Precision = 2, CanPlot=true },
        { SingleText = "A1", Precision = 2, CanPlot=true },
        { SingleText = "A2", Precision = 2, CanPlot=true },
        { SingleText = "A3", Precision = 2, CanPlot=true },
        { SingleText = "A4", Precision = 2, CanPlot=true },
        { SingleText = "A5", Precision = 2, CanPlot=true },
    }    
})


