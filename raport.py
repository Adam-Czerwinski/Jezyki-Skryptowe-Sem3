import glob
import datetime
import os
import subprocess
import webbrowser

#aktualna data z własnym formatowaniem
now = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
#ilość plików out*.txt
ilePlikow = len(glob.glob1("./out/","out*.txt"))
#ścieżka do raportu o nazwie aktualnego czasu
filepathWrite = os.path.join(os.path.dirname(__file__), 'raport',now + '.html')
#otwarcie pliku do odczytu danych
filepathRead = os.path.join(os.path.dirname(__file__), 'out','out')

#-------------------------wczytywanie danych z pliku

if ilePlikow>0:
    #otwarcie zawartosci html
    html = """
        <!DOCTYPE html>
        <html>
        <head>
        <link href="../design.css" type="text/css" rel="stylesheet">
        <title>"""+now+"""</title>
        </head>
        <body>
            <center>
            <h1>""" + """Raport z dnia """ + str(datetime.datetime.now().strftime("%Y-%m-%d %H-%M-%S")) + """</h1>
            <table>
            """

    #petla dopisujaca do pliku html
    for i in range(1,ilePlikow + 1):

        #sciezka do pliku
        filepath = filepathRead + str(i) + '.txt'

        #pomocnicza zmienna zeby wyodrebnic nazwe pliku
        temp = filepath.split('\\')

        #nazwa pliku
        filename = temp[len(temp) - 1]
        try:
            with open(filepath, 'r') as content_file:

                #content zawiera dane w pliku
                content = content_file.read()

                #podzielenie danych ze wzgledu na nowe linie
                dzialania = content.split("\n")

                #dopisywanie do pliku html wierszy
                html+="""
                    <tr><th>Plik: """ + filename + """</th></tr>
                """
        except:
            print("Problem z wczytaniem zawartości z pliku "+filename)
            subprocess.call('goto :Koniec')
        #wypisywanie działań
        for x in range(0,len(dzialania)-1):
            html+="<tr><td>" + dzialania[x] + "</td></tr>"
    
    #zamkniecie zawartosci html
    html+="""
            </table>
            </center>
        </body>
        </html>
    """

    #-------------------------koniec wczytywania danych z pliku

    #otwarcie pliku do zapisu danych
    fileWrite = open(filepathWrite,'w')

    #wypisanie do pliku
    fileWrite.write(html)

    #zamkniecie pliku
    fileWrite.close()

    webbrowser.open(filepathWrite)