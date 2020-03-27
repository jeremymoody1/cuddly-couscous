#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

//Prompt input, calculate checksum, check for card length and starting digits, print out : AMEX, MASTERCARD, VISA, or INVALID.


int main(void)
{
    long long cardnum = get_long_long("Number: ");
    long long length = cardnum;
    long long cardnum2 = cardnum;
    int counter = 0;
    bool isVisa = false;
    bool isAmex = false;
    bool isMASTERCARD = false;
    bool isValidLength = false;
    bool isValidHash = false;
    bool nomatch = false;
    


    do
    {
        length = (length / 10); //getting length of cardnumber.
        counter++;
    }
    while(length > 0);

    if(counter == 15 || counter == 16 || counter == 13) //checking for valid lengths.
    {
        isValidLength = true;
    }
  
    int temp[counter];

    for(int i = 0; i < counter; i++)
    {
        temp[i] = cardnum % 10;
        cardnum = cardnum / 10;
    }//makes and int array the size of the card number and then transcribes card number backwards to the array.
    

    int arraycardnum[counter];

    for(int i = 0; i < counter; i++)
    {
        arraycardnum[(counter - i - 1)] = temp[i];  
    }//Converts the backwards card number array to another array that is forwards now (arraycardnum[]).



    int secondcounter = 0;
    for(int i = counter - 1; i >= 0; i = i - 2) //Beginning of hash solution. Starts at 2nd to last digit and begins multiplying by 2 until it reaches the beginning.
    {
        secondcounter++;
    }
    int holder[secondcounter];
    int j = 0;

    for(int i = counter -2; i >= 0; i = i -2)
    {
        holder[j] = arraycardnum[i] * 2;
        j++;
    }

    int firstsum = 0;
    int secondsum = 0;

    for(int k = 0; k < secondcounter; k++)
    {
        if(holder[k] < 10)
        {
            firstsum = firstsum + holder[k];
        }
        else if(holder[k] >= 10)
        {
            firstsum = firstsum + (holder[k] % 10) + 1;
        }
    }

    for(int i = counter - 1; i >= 0; i = i -2)
    {
        secondsum = secondsum + arraycardnum[i];
    }

    if((firstsum + secondsum) % 10 == 0) //Final hash validation. Requires the total sum to be a multiple of 10.
    {
        isValidHash = true;
    }

    if (arraycardnum[0] == 3)
    {
        if(arraycardnum[1] == 4 || arraycardnum[1] == 7)
        {
            isAmex = true;
        }  
    }

    if (arraycardnum[0] == 5)
    {
        if(arraycardnum[1] >=1 && arraycardnum[1] <= 5)
        {
            isMASTERCARD = true;
        }
    }

    if (arraycardnum[0] == 4)
    {
        isVisa = true;
    }

    if (isVisa == false && isMASTERCARD == false && isAmex == false)
    {
        nomatch = true;
    }

    if(isValidLength == false || isValidHash == false || nomatch == true)
    {
        printf("INVALID\n");
    }

    else if (isVisa == true)
    {
        printf("VISA\n");
    }

    else if (isMASTERCARD == true)
    {
        printf("MASTERCARD\n");
    }

    else if (isAmex == true)
    {
        printf("AMEX\n");
    }

}


