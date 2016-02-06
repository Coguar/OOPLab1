replace.exe TrueInput.txt output1.txt ma mama
echo '----Right replace----'
replace.exe TrueInput.txt output2.txt ma
echo '----Without replace----'
replace.exe TrueInput.txt output1.txt
echo '----Only 2 arguments----'
replace.exe TrueInput.txt output1.txt ma mama oneMoreArg
echo '----1 more argument(5)----'
replace.exe TrueInput.tx output1.txt ma mama
echo '----Wrong input----'
replace.exe TrueInput.txt output1.tx ma mama
echo '----Wrong output----'
replace.exe DocInput.txt output1.txt ma mama
echo '----Input not found----'
replace.exe DocInput.docx output1.txt ma mama
echo '----Wrong type Input---'
PAUSE
