from pandas import *
from numpy import *



def GetTSinfo(testrunN,varN):
    File = r"C:\CM_Projects\PyTestAutomation\Scenario.xlsx"
    TS = read_excel(File)
    trName = TS.iloc[testrunN,0]
    trParam = TS.iloc[testrunN,1]
    trVal = TS.iloc[testrunN,2]

    print(trName, trParam, trVal)
    #testrunName = TS.ix[0,1]
    print(type(trName),type(trParam),type(trVal))



def main():
    GetTSinfo(1,1)

if __name__ == "__main__":
    main()
