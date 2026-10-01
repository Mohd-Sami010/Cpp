#include <iostream>
#include <string>
using namespace std;

class Account
{
protected:
    int pin;
    float balance = 0;

    string transactionHistory[100];
    int transactionHistoryIndex = 0;
    int accNumber;
    string customerName;

public:
    Account() {}
    Account(string customerName, int accNumber, int pin)
    {
        this->customerName = customerName;
        this->accNumber = accNumber;
        this->pin = pin;
    }
    void DepositMoney(float amount)
    {
        if (amount <= 0)
        {
            cout << "Deposite amount must be greater than 0!" << endl;
            return;
        }
        balance += amount;
        string transactionLog = "Deposited Rs. " + to_string(amount) + " to your account, new balance Rs. " + to_string(balance);
        transactionHistory[transactionHistoryIndex++] = transactionLog;
        cout << transactionLog << endl;
    }
    bool WithdrawMoney(float amount, int pin)
    {
        if (this->pin != pin)
        {
            cout << "Incorrect pin, Transaction failed!" << endl;
            return false;
        }
        if (balance < amount)
        {
            cout << "Insufficient balance, Transaction failed!" << endl;
            return false;
        }

        balance -= amount;
        string transactionLog = "Withdrawn Rs. " + to_string(amount) + " from your account, new balance Rs. " + to_string(balance);
        transactionHistory[transactionHistoryIndex++] = transactionLog;
        cout << transactionLog << endl;
        return true;
    }
    void ShowDetails()
    {
        cout << customerName << " Ac no: " << accNumber << " Balance: Rs. " << balance << endl;
    }
    void ShowTransactionHistory(int pin)
    {
        if (this->pin != pin)
        {
            cout << "Incorrect pin" << endl;
            return;
        }
        cout << "Transaction history of " << customerName << endl;
        for (int i = 0; i < transactionHistoryIndex; i++)
        {
            cout << transactionHistory[i] << endl;
        }
        cout << "--- End ---" << endl;
    }

    string GetCustomerName()
    {
        return customerName;
    }
};

Account accounts[10];
int lastAccountNumber = 0;

int GetValidAccNumber()
{
    int accNumber;
    cout << "Enter account number: ";
    cin >> accNumber;

    if (accNumber > lastAccountNumber)
    {
        cout << "No account Exists with this account number" << endl;
        return -1;
    }
    cout << "Account holder name: " << accounts[accNumber].GetCustomerName() << endl;
    return accNumber;
}

void HandleCreateAccount()
{
    cout << "\nCreating Account" << endl;
    string accHolderName;
    int accNumber = lastAccountNumber++;
    int pin;

    cout << "Enter customer name: ";
    cin >> accHolderName;

    cout << "Enter new sequrity pin: ";
    cin >> pin;

    Account newAccount(accHolderName, accNumber, pin);
    accounts[accNumber] = newAccount;

    cout << "Account created successfully" << endl;
}
void HandleDeposit()
{
    cout << "Deposit Money" << endl;
    int accNumber = GetValidAccNumber();
    if (accNumber < 0)
        return;

    float depositAmount;
    cout << "Enter deposit amount: ";
    cin >> depositAmount;

    accounts[accNumber].DepositMoney(depositAmount);
}
void HandleWithdraw()
{
    cout << "\nWithdraw Money" << endl;
    int accNumber = GetValidAccNumber();
    if (accNumber < 0)
        return;

    float withdrawAmount;
    cout << "Enter withdraw amount: ";
    cin >> withdrawAmount;

    int pin;
    cout << "Enter sequrity pin: ";
    cin >> pin;

    accounts[accNumber].WithdrawMoney(withdrawAmount, pin);
}
void PrintAccountsDetails()
{
    cout << "\nAll accounts:" << endl;
    for (int i = 0; i < lastAccountNumber; i++)
    {
        accounts[i].ShowDetails();
    }
}
void MoneyTransfer()
{
    cout << "\nMoney Transfer" << endl;

    cout << "Sender details" << endl;
    int senderAccNumber = GetValidAccNumber();
    if (senderAccNumber < 0)
        return;

    float transferAmount;
    cout << "Enter transfer amount: ";
    cin >> transferAmount;

    int pin;
    cout << "Enter your pin: ";
    cin >> pin;

    cout << "Receiver details" << endl;
    int receiverAccNumber = GetValidAccNumber();
    if (receiverAccNumber < 0)
        return;

    if (!accounts[senderAccNumber].WithdrawMoney(transferAmount, pin))
        return;
    accounts[receiverAccNumber].DepositMoney(transferAmount);

    cout << "\nMoney Transfer Completed!" << endl;
}
void ShowTransactionHistory()
{
    cout << "\nTransaction History" << endl;
    int accNumber = GetValidAccNumber();
    if (accNumber < 0)
        return;

    int pin;
    cout << "Enter your pin: ";
    cin >> pin;

    accounts[accNumber].ShowTransactionHistory(pin);
}

int main()
{
    char exit;
    do
    {
        cout << "BANK SYSTEM" << endl;
        cout << "1. Create account\n2. Deposit money\n3. Withdraw money\n4. Show accounts\n5. Money Transfer\n6. Transaction history" << endl;
        cout << "Enter your option: ";

        int option;
        cin >> option;

        switch (option)
        {
        case 1:
            HandleCreateAccount();
            break;

        case 2:
            HandleDeposit();
            break;
        case 3:
            HandleWithdraw();
            break;
        case 4:
            PrintAccountsDetails();
            break;
        case 5:
            MoneyTransfer();
            break;
        case 6:
            ShowTransactionHistory();
            break;
        }

        cout << "\nWanna exit? ";
        cin >> exit;
    } while (exit != 'y');
    return 0;
}