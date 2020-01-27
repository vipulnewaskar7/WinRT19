' for 'Form'
Imports System.Windows.Forms
' .Net callable dll created by using tlbimp.exe utility
Imports AutomationServerTypeLibForDotNet

Public Class  VBClient
    Inherits Form
    Public Sub New()
        MsgBox("str")
        Dim ObjIMyMath As Object
        Dim MyRef As New CMyMathClass
        ObjIMyMath = MyRef
        Dim iNum1 = 750
        Dim iNum2 = 250
        Dim iSum = ObjIMyMath.SumOfTwoIntegers(iNum1, iNum2)
        Dim str As String = String.Format("Sum of {0} and {1} is {2}", iNum1, iNum2, iSum)
        ' default message box with only 1 button of 'Ok'
        MsgBox(str)
        Dim iSubtract = ObjIMyMath.SubtractionOfTwoIntegers(iNum1, iNum2)
        str = String.Format("Subtraction of {0} and {1} is {2}", iNum1, iNum2, iSubtract)
        MsgBox(str) 
        ' End works as DestroyWindow(hwnd)
        End
    End Sub

    <STAThread()>
    Shared Sub Main()
        Application.EnableVisualStyles()
        Application.Run(New VBClient())
    End Sub
End Class

        
