def instructiuni():
    print("Cateva reguli de utilizare:")
    print("-pentru AND se va citi '&';")
    print("-pentru NOT se va citi '~';")
    print("-pentru OR se va citi '|';")
    print("-pentru IMPLICA se va citi '-';")
    print("-pentru ECVHIVALENT se va citi '=';")
    print("-pentru PARANTEZA DESCHISA se va citi '(';")
    print("-pentru PARANTEZA INCHISA se va citi ')';")
    print("-pentru PROPOZITIILE ATOMICE se vor folosi litere simple (mari sau mici), NU litere cu indecsi, NU litere dublate.")
    print("-NU va fi introdus niciun spatiu intre elementele expresiei (fie ca este vorba despre conectori sau propozitii atomice\n\n")
    #ultimul print va fi programat

def verificaConector(caracter,conectori):
    lungime=len(conectori)
    for j in range(0,lungime):
        if caracter==conectori[j]:
            return 1
    return 0

def verificaPropatomice(caracter,propatomice):
    lungime=len(propatomice)
    for j in range(0,lungime):
        if caracter==propatomice[j]:
            return 1
    return 0

def verificaCaractere(caracter,caractere):
    lungime=len(caractere)
    for j in range(0,lungime):
        if caracter==caractere[j]:
            return 1
    return 0

def validareExpresiaIntrodusa(text,caractere,conectori,propatomice):
    n=len(text)
    deschise, inchise, operatori, propozitii=0,0,0,0
    for i in range(0,n):
        if text[i]>='a' and text[i]<='z':
            print("Expresia introdusa nu este formula propozitionala\nAu fost introduse caractere mici; ele nu sunt considerate propozitii atomice")
            exit(0)
        if verificaConector(text[i],conectori)==1:
            operatori+=1
            if verificaConector(text[i+1],conectori)==1:
                print("Expresia nu este formula propozitionala\nAu fost introdusi 2 conectori unul dupa altul")
                exit(0)
            if verificaPropatomice(text[i+1],propatomice)==0 and text[i+1]!='(':
                print("Expresia nu este formula propozitionala\n")
                exit(0)
        if verificaPropatomice(text[i],propatomice)==1:
            propozitii+=1
            # if verificaConector(text[i+1],conectori)==0 and text[i+1]!=')' and i<=n:
            #     print("Expresia nu este formula propozitionala")
            #     exit(0)
        if verificaCaractere(text[i],caractere)==0:
            print("Expresia introdusa nu este formula propozitionala\nCaracterul", end=" ")
            print(text[i], end=" nu este permis in expresie")
            exit(0)
        if text[i]=='(':
            deschise+=1
            if text[i+1]==')' and verificaCaractere(text[i+1],caractere)==0 and verificaPropatomice(text[i+1],propatomice)==0:
                print("Expresia nu este formula propozitionala\n")
                exit(0)
        if text[i]==')':
            if deschise==0:
                print("Expresia introdusa nu este formula propozitionala\nA fost introdusa o paranteza inchisa inainte de cea deschisa")
                exit(0)
            inchise+=1
        if text[i]=='~':
            if verificaPropatomice(text[i+1],propatomice)==0 and text[i+1]!='(':
                print("Expresia nu este formula propozitionala\n")
                exit(0)
    if inchise!=deschise:
        print("Expresia introdusa nu este formula propozitionala\nNumarul de paranteze deschise nu coincide cu cel al parantezelor inchise")
        exit(0)
    elif deschise!=operatori:
        print("Expresia introdusa nu este formula propozitionala\nNumarul de perechi de paranteze nu corespunde numarului de operatori")
        exit(0)
    if propozitii!=0 and operatori==0:
        print("Expresia introdusa nu este formula propozitionala\nExpresia nu contine conectori logici")
        exit(0)
    if propozitii==0 and operatori!=0:
        print("Expresia introdusa nu este formula propozitionala\nExpresia nu contine propozitii atomice")
        exit(0)
    if inchise==deschise and propozitii==1 and operatori==0:
        print("Expresia nu este formula propozitionala\nExpresia este de forma (P); aceasta forma nu este considerata o formula bine formata")
        exit(0)
    for i in range(0,n-1):
        if verificaPropatomice(text[i],propatomice)==1:
            if verificaConector(text[i+1],conectori)==0 and text[i+1]!=')':
                print("Expresia nu este formula propozitionala")
                exit(0)
    print("Expresia este formula propozitionala")



instructiuni()
text=str(input())
caractere="QWERTYUIOPASDFGHJKLZXCVBNM&~|-=() "
conectori="&~|-="
propatomice="QWERTYUIOPASDFGHJKLZXCVBNM"
validareExpresiaIntrodusa(text,caractere,conectori,propatomice)
