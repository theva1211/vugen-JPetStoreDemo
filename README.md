# JpetStore_PurchasePetAnimal — LoadRunner VuGen Script

## Overview

This is a LoadRunner Virtual User Generator (VuGen) script that simulates an end-to-end pet purchasing workflow on the **JPetStore** demo application hosted at `https://petstore.octoperf.com`. The script uses the **Web HTTP/HTML** protocol and was recorded using VuGen 2022.

## Business Flow

The script replicates a complete user journey through 10 transactions:

| Step | Transaction | Description |
|------|------------|-------------|
| 1 | T01_Launch | Opens the JPetStore homepage |
| 2 | T02_Login | Navigates to Sign In page and submits credentials |
| 3 | T03_Navigate_PetAnimal | Browses to a pet animal category (Dogs, Cats, Fish, Birds, or Reptiles) |
| 4 | T04_Select_ProductID | Selects a random product from the chosen category |
| 5 | T05_Select_ItemID | Selects a random item from the product listing |
| 6 | T06_AddToCart | Adds the selected item to the shopping cart |
| 7 | T07_ProceedToCheckOut | Proceeds to the checkout page |
| 8 | T08_ClickContinue | Submits billing/payment details and continues |
| 9 | T09_ClickConfirm | Confirms the order and captures the Order ID |
| 10 | T10_Logout | Signs out of the application |

## Correlation

The script handles the following dynamic values using `web_reg_save_param_ex`:

| Correlated Parameter | Source | Purpose |
|---------------------|--------|---------|
| `c_jessionid` | JSESSIONID cookie | Session management — appended to URLs |
| `c_fp` | Hidden form field `__fp` | Anti-CSRF token for login form |
| `c_sourcePage` | Hidden form field `_sourcePage` | Form state tracking for login |
| `c_productID` | Product listing page (Ordinal=All) | Captures all product IDs for random selection |
| `c_itemID` | Item listing page (Ordinal=All) | Captures all item IDs for random selection |
| `c_fpID` | Hidden form field `__fp` | Anti-CSRF token for checkout form |
| `c_sourcePageID` | Hidden form field `_sourcePage` | Form state tracking for checkout |
| `p_orderID` | Order confirmation page | Captures the generated Order ID |

## Parameterisation

All test data is externalised into `.dat` files for data-driven execution:

### p_username.dat (Primary data file — 13 columns, comma-delimited)

Contains user credentials and billing information. All user-related parameters are linked using **"Same line as p_username"** to keep data consistent per virtual user.

| Column | Parameter | Sample Value | Description |
|--------|-----------|-------------|-------------|
| 1 | p_username | j2ee | Login username |
| 2 | p_pwd | j2ee | Login password |
| 3 | p_cardType | Visa | Payment card type |
| 4 | p_cardNumber | 999 9999 9999 9999 | Payment card number |
| 5 | p_expiryDate | 12/03 | Card expiry date |
| 6 | p_FirstName | ABC | Billing first name |
| 7 | p_LastName | user | Billing last name |
| 8 | p_Address1 | Lb Nagar | Billing address line 1 |
| 9 | p_Address2 | *(empty)* | Billing address line 2 |
| 10 | p_City | Hyderabad | Billing city |
| 11 | p_State | Telangana | Billing state |
| 12 | p_Zip | 500034 | Billing zip code |
| 13 | p_Country | India | Billing country |

**Selection method:** Sequential, new value each iteration.

### p_AnimalName.dat

| Value |
|-------|
| BIRDS |
| FISH |
| CATS |
| DOGS |
| REPTILES |

**Selection method:** Random, new value each iteration. This ensures each virtual user browses a different pet category.

### p_URL.dat

| Value |
|-------|
| https://petstore.octoperf.com |

**Selection method:** Sequential, loaded once. Update this file if pointing to a different JPetStore environment.

## Verification (Content Checks)

Each transaction includes a `web_reg_find` to validate the server response:

| Transaction | Verification Text |
|------------|------------------|
| T01_Launch | "Sign In" |
| T02_Login | "Welcome {p_FirstName}" |
| T03_Navigate_PetAnimal | "Product ID" |
| T05_Select_ItemID | "Add to Cart" |
| T06_AddToCart | "Proceed to Checkout" |
| T07_ProceedToCheckOut | "Ship to different address..." |
| T09_ClickConfirm | "Thank you, your order has been submitted." |
| T10_Logout | "Sign In" |

## Script Files

| File | Purpose |
|------|---------|
| `Action.c` | Main script with all transactions, correlations, and parameterisation |
| `vuser_init.c` | Initialisation (currently empty) |
| `vuser_end.c` | Cleanup (currently empty) |
| `JpetStore_PurchasePetAnimal.prm` | Parameter definitions and configuration |
| `JpetStore_PurchasePetAnimal.usr` | Script metadata (protocol, version, actions) |
| `default.cfg` | Runtime settings (think time, logging, browser emulation) |
| `default.usp` | Run logic profile |
| `p_username.dat` | User credentials and billing data |
| `p_AnimalName.dat` | Pet category names |
| `p_URL.dat` | Application base URL |
| `globals.h` | Global header file |
| `data/` | Recording snapshots and session data |

## Prerequisites

- **LoadRunner Professional** or **VuGen** 2022 or later
- Network access to `https://petstore.octoperf.com`
- Valid user accounts registered on the JPetStore application (default: `j2ee` / `j2ee`)

## How to Run

1. Open **VuGen** (Virtual User Generator)
2. Go to **File → Open Script** and navigate to the script folder
3. Open `JpetStore_PurchasePetAnimal.usr`
4. Before running, verify the application is accessible by visiting `https://petstore.octoperf.com` in a browser
5. Update `p_username.dat` if you need additional test users
6. Update `p_URL.dat` if using a different JPetStore environment
7. Click the **Run** button (or press F5) to replay the script
8. Check the **Replay Log** for pass/fail status of each transaction

## Runtime Settings

| Setting | Value |
|---------|-------|
| Think Time | Recorded (as-is from recording) |
| Iterations | 1 (increase for multiple iterations) |
| Log Level | Extended logging with parameter substitution |
| Browser Emulation | Firefox 148.0 (custom user agent) |
| HTTP Version | 1.1 |
| Keep-Alive | Enabled |

## Techniques Used

- **Dynamic correlation** of JSESSIONID, `_sourcePage`, and `__fp` hidden form fields using `web_reg_save_param_ex`
- **Random selection** from correlated arrays using `lr_paramarr_random` for both Product ID and Item ID — this creates realistic, varied user behaviour
- **Data-driven testing** with external `.dat` files and linked parameters (Same line as p_username)
- **Content verification** with `web_reg_find` on every transaction
- **Transaction naming convention**: `ScenarioName_TransactionNumber_ActionDescription`

## Adding More Test Users

To add more users for load testing, append rows to `p_username.dat` following the same comma-delimited format:

```
username,password,cardType,cardNumber,expiryDate,firstName,lastName,address1,address2,city,state,zip,country
```

Make sure each user account is pre-registered on the JPetStore application before running the test.

## Known Considerations

- The JPetStore OctoPerf instance (`https://petstore.octoperf.com`) is a public demo site. Do not run heavy load tests against it — use it for single-user VuGen replay and small-scale scenarios only.
- JSESSIONID correlation is critical. If replay fails with HTTP 500 errors, check that the correlation boundaries (`LB=JSESSIONID=`, `RB=; Path`) still match the server response.
- The `_sourcePage` and `__fp` values change with each session and must be correlated for successful form submissions.
