@echo off
chcp 1250 >nul
echo Program do dzialania wymaga przynajmniej jednego pliku "in1.txt" w katalogu "in". Musi zawieraæ prawid³owe dane.
echo Mozna uzyc wiecej plikow inkrementujac wartosc liczbowa w nazwie pliku np. "in2.txt", "in3.txt" itd.
echo Nacisnij enter by kontynuowac
pause >nul

if exist "%cd%\in\in1.txt" (
  echo Znaleziono pliki!

  IF NOT EXIST out (mkdir out)
  IF NOT EXIST raport (mkdir raport)
  IF NOT EXIST backup (mkdir backup)

  xcopy /s/h/e/k/f/c/y .\out\*.* .\backup\ >nul
  del /q .\out\*.* >nul

   
  forfiles /P "%cd%"\in\ /M in*.txt /C "cmd /c echo Przekazywanie pliku @fname..."
  forfiles /P "%cd%"\in\ /M in*.txt /C "cmd /c call ..\executable.exe @path"

) else ( goto :BrakPliku )

if exist "%cd%\out\out1.txt" (
echo.
echo Tworzenie raportu..
python raport.py

echo.
echo Gotowe.
echo Wyniki programu znajduja sie w katalogu "out" oraz w katalogu "raport"
)

:Koniec
echo.
echo Koniec programu!
pause >nul
exit

:BrakPliku
echo.
echo Nie znaleziono plikow w katalogu "in"
goto :Koniec