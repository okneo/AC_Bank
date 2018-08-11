### Functions
AC Bank, the short for Accepted Bank, is a mini project aiming at simulating the system of a real commercial bank.
<br/><br/>We tried to describe our project in the most natural way to the IDE. We neither made it too complex nor made it too simple on purpose.
However, payment interface is not considered in the project, because settling system does not belong to an exact commercial bank.
<br/><br/>The project of simulated bank has three branches of visible account. 
Root account, Bank account and User account. User account contains CreditCard account, DebitCard account and OnlineBanking account. Each account type comes from a class. All visible account classes inherit from the base class AccountType. Base class AccountType offers several ultilities. Each account has an Interface, provides an index of functions this account type has. 
#### Account creating
Root account can create Bank accounts and approve CreditCard accounts application sent by Bank accounts. Bank accounts can create User accounts.
#### Account Functions
Every account is able to reset its own password. Root account manages basic data of this bank, such as interest, CreditCard info, bank asset, etc. Bank accounts mainly manage User accounts, such as reset a password of a User account, submit CreditCard application, create User accounts, view info of a User account, etc.
