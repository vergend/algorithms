#Requires AutoHotkey v2.0+
SendMode "Input"  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir A_ScriptDir  ; Ensures a consistent starting directory.

Global oVoice := ComObject("SAPI.SpVoice"), voices := oVoice.GetVoices()

speak(phrase,voiceNumber:=1,rate:=0,vol:=100) {
    oVoice.Volume := vol
    oVoice.Rate := rate
    oVoice.Voice := voices.Item(voiceNumber - 1)
    SVSFlagsAsync := 1
    oVoice.Speak(phrase, SVSFlagsAsync)
}

~Esc::
{
    SVSFPurgeBeforeSpeak := 2
    oVoice.Speak("",SVSFPurgeBeforeSpeak)
}

~LButton::
{
SetMouseDelay 1
KeyWait "LButton"
if (A_TimeSinceThisHotkey > 500)
{
A_Clipboard := "-"
Sleep 10
Send "^c"
Loop 10
{
  if ("-" == A_Clipboard)
  {
    Sleep 10
  }
  else
  {
    break
  }
}

A_StringCaseSense := "On"
dict:=[["†"," dagger "],["PDE"," P D E"],["¯"," bar "],["×"," times "],["∗"," star "],["′"," prime "],["ξ"," ksi "],["ζ"," zeta "],["χ"," chi "],["Υ"," upsilon "],["σ"," sigma "],["Σ"," sigma "],["θ"," theta "],["π"," pie "],["Ψ"," psi "],["ρ"," rho "],["α"," alpha "],["κ"," kappa "],[" A "," Ay "],["∼"," on the order of "],[""," much less than "],[""," much greater than "],[">"," greater "],["<"," lesser "],["∞"," infinity "],["ω"," omega "],["∈"," element of "],["ψ"," psi "],["→"," going to "],["φ"," phi "],["Φ"," phi "],["ǫ"," epsilon "],["ε"," epsilon "],[""," epsilon "],["Ω"," omega "],["η"," aeta "],["γ"," gamma "],["λ"," lambda "],["Λ"," lambda "],["τ"," tau "],["δ"," delta "],["∆"," delta "],["µ"," mu "],["ν"," nu "],["ϕ"," phi "],["AdS"," A D S "],["∂"," del "],["∇"," naablaa "],["§"," section "],["+"," plus "],["−"," minus "],["LHS"," left hand side "],["RHS"," right hand side "],["OPE"," O P E "],["andelstam","aandelshtaam"],["nitarity","nitaeryty"],["Euler","Oiler"],["Einstein","Aaynshtaayne "]]
for index, element in dict ; Enumeration is the recommended approach in most cases.
{
A_Clipboard := StrReplace(A_Clipboard, element[1],element[2])
}
speak(A_Clipboard,1,5,100)
}
}
return