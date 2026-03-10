# 🐾 JpetStore_PurchasePetAnimal — LoadRunner VuGen Script

A LoadRunner VuGen performance test script that simulates an end-to-end **pet purchasing workflow** on the **JPetStore** demo application hosted at `https://petstore.octoperf.com`, built using the Web HTTP/HTML protocol.

---

## 🎯 Project Overview

This script demonstrates:

- Session management with JSESSIONID cookie correlation
- Anti-CSRF token handling (`__fp` and `_sourcePage` hidden form fields)
- Random product and item selection using `lr_paramarr_random`
- Data-driven testing with a multi-column parameterised `.dat` file
- End-to-end purchase workflow including billing form submission
- Order ID capture from the confirmation page
- Content verification with `web_reg_find` on every transaction
- Web HTTP/HTML protocol scripting in VuGen

---

## 📁 Project Structure

```
JpetStore_PurchasePetAnimal/
├── Action.c                               # Main script with all transactions, correlations, and parameterisation
├── vuser_init.c                           # Virtual user initialisation (empty)
├── vuser_end.c                            # Virtual user teardown (empty)
├── globals.h                              # Global variables (thinktime, strProductID, strItemID)
├── JpetStore_PurchasePetAnimal.prm        # Parameter definitions and configuration
├── JpetStore_PurchasePetAnimal.usr        # Script metadata (protocol, version, actions)
├── default.cfg                            # Runtime settings (iterations, logging, think time)
├── default.usp                            # Run logic profile
├── p_URL.dat                              # Application base URL
├── p_username.dat                         # User credentials and billing data (13 columns)
├── p_AnimalName.dat                       # Pet category names
├── p_cardNumber.dat                       # Card number reference file
├── lrw_custom_body.h                      # Custom body header
├── WebSocketBuffer.h                      # WebSocket buffer header
└── data/                                  # Recording snapshots, request/response headers, static assets
```

---

## 🚀 Quick Start

### Prerequisites

- LoadRunner Professional / VuGen 2022 or later
- Network access to `https://petstore.octoperf.com`
- Valid user accounts pre-registered on the JPetStore application (default: `j2ee` / `j2ee`)

### Run the Script

```bash
# 1. Open VuGen and load the script
File → Open Script → Select JpetStore_PurchasePetAnimal.usr

# 2. Verify the application is accessible
Open https://petstore.octoperf.com in a browser

# 3. Update credentials if needed
Edit p_username.dat with additional test users

# 4. Update target URL (if using a different environment)
Edit p_URL.dat with the correct base URL

# 5. Compile the script
Press Ctrl+F5 to compile and verify no errors

# 6. Run the script
Press F5 to replay
```

### Access Points

| Service | URL |
|---------|-----|
| JPetStore Application | `https://petstore.octoperf.com` |
| Sign In Page | `{p_URL}/actions/Account.action?signonForm=` |
| Pet Category | `{p_URL}/actions/Catalog.action?viewCategory=&categoryId={p_AnimalName}` |
| Checkout | `{p_URL}/actions/Order.action?newOrderForm=` |
| Order Confirmation | `{p_URL}/actions/Order.action?newOrder=&confirmed=true` |

---

## 🛠️ Tech Stack

**Performance Testing**
- LoadRunner VuGen 2022 — Script recording and replay
- Web HTTP/HTML Protocol — HTTP/1.1 request simulation

**Target Application**
- JPetStore — Java-based demo e-commerce application (OctoPerf hosted)
- Struts-based MVC web application
- Session-based authentication with JSESSIONID

---

## 📊 Business Flow

The script replicates a complete user journey through **10 transactions**:

| Step | Transaction | Description |
|------|-------------|-------------|
| 1 | `JpetStore_S01_PurchaseAnimal_T01_Launch` | Opens the JPetStore homepage |
| 2 | `JpetStore_S01_PurchaseAnimal_T02_Login` | Navigates to Sign In page and submits credentials |
| 3 | `JpetStore_S01_PurchaseAnimal_T03_Navigate_PetAnimal` | Browses to a randomly selected pet category |
| 4 | `JpetStore_S01_PurchaseAnimal_T04_Select_ProductID` | Selects a random product from the chosen category |
| 5 | `JpetStore_S01_PurchaseAnimal_T05_Select_ItemID` | Selects a random item from the product listing |
| 6 | `JpetStore_S01_PurchaseAnimal_T06_AddToCart` | Adds the selected item to the shopping cart |
| 7 | `JpetStore_S01_PurchaseAnimal_T07_ProceedToCheckOut` | Proceeds to the checkout page |
| 8 | `JpetStore_S01_PurchaseAnimal_T08_ClickContinue` | Submits billing and payment details |
| 9 | `JpetStore_S01_PurchaseAnimal_T09_ClickConfirm` | Confirms the order and captures the Order ID |
| 10 | `JpetStore_S01_PurchaseAnimal_T10_Logout` | Signs out of the application |

---

## 📚 Features

### ✅ Implemented

- End-to-end pet purchase workflow (10 transactions)
- JSESSIONID session correlation appended to all post-login URLs
- Anti-CSRF token correlation (`__fp` and `_sourcePage`) for both login and checkout forms
- Random product ID selection from full product array using `lr_paramarr_random`
- Random item ID selection from full item array using `lr_paramarr_random`
- Order ID capture (`p_orderID`) from the order confirmation page
- Content verification (`web_reg_find`) on every transaction
- Data-driven parameterisation with 13-column `p_username.dat`
- Random pet category selection per iteration (BIRDS, FISH, CATS, DOGS, REPTILES)
- Transaction naming convention: `ScenarioID_ScenarioName_TransactionNumber_ActionDescription`

### 🚧 Planned

- Additional scenarios (e.g. Edit Account, Search for Pet, Remove from Cart)
- Multi-user load scenario configuration in Controller
- Controller scenario setup for concurrent virtual users
- Expanded `p_username.dat` with more diverse test user data

---

## 🔗 Correlation

The script handles the following dynamic values using `web_reg_save_param_ex`:

| Correlated Parameter | Source | Purpose |
|---------------------|--------|---------|
| `c_jessionid` | JSESSIONID cookie | Session ID — appended to all post-login URLs to maintain user session |
| `c_fp` | Hidden field `__fp` (login page) | Anti-CSRF token — submitted in the T02 login POST form |
| `c_sourcePage` | Hidden field `_sourcePage` (login page) | Form state token — submitted in the T02 login POST form |
| `c_productID` | Product listing page (`Ordinal=All`) | Captures all available product IDs for random selection in T04 |
| `c_itemID` | Item listing page (`Ordinal=All`) | Captures all available item IDs for random selection in T05 |
| `c_fpID` | Hidden field `__fp` (checkout page) | Anti-CSRF token — submitted in the T08 checkout POST form |
| `c_sourcePageID` | Hidden field `_sourcePage` (checkout page) | Form state token — submitted in the T08 checkout POST form |
| `p_orderID` | Order confirmation page (`Order #`) | Captures the generated Order ID after successful purchase |

---

## 🗂️ Parameterisation

### p_username.dat — Primary data file (13 columns, comma-delimited)

All user-related parameters are linked using **"Same line as p_username"** to keep data consistent per virtual user.

| Column | Parameter | Sample Value | Description |
|--------|-----------|-------------|-------------|
| 1 | `p_username` | j2ee | Login username |
| 2 | `p_pwd` | j2ee | Login password |
| 3 | `p_cardType` | Visa | Payment card type |
| 4 | `p_cardNumber` | 999 9999 9999 9999 | Payment card number |
| 5 | `p_expiryDate` | 12/03 | Card expiry date |
| 6 | `p_FirstName` | ABC | Billing first name |
| 7 | `p_LastName` | user | Billing last name |
| 8 | `p_Address1` | Lb Nagar | Billing address line 1 |
| 9 | `p_Address2` | *(empty)* | Billing address line 2 |
| 10 | `p_City` | Hyderabad | Billing city |
| 11 | `p_State` | Telangana | Billing state |
| 12 | `p_Zip` | 500034 | Billing zip code |
| 13 | `p_Country` | India | Billing country |

**Selection method:** Sequential, new value each iteration.

### p_AnimalName.dat

| Value |
|-------|
| BIRDS |
| FISH |
| CATS |
| DOGS |
| REPTILES |

**Selection method:** Random, new value each iteration. Ensures each virtual user browses a different pet category.

### p_URL.dat

| Value |
|-------|
| https://petstore.octoperf.com |

**Selection method:** Sequential, loaded once. Update this file if pointing to a different JPetStore environment.

---

## ✅ Verification (Content Checks)

Each transaction includes a `web_reg_find` to validate the server response:

| Transaction | Verification Text |
|------------|------------------|
| T01_Launch | `Sign In` |
| T02_Login | `Welcome {p_FirstName}` |
| T03_Navigate_PetAnimal | `Product ID` |
| T04_Select_ProductID | `Item ID` |
| T05_Select_ItemID | `Add to Cart` |
| T06_AddToCart | `Proceed to Checkout` |
| T07_ProceedToCheckOut | `Ship to different address...` |
| T08_ClickContinue | `Return to Main Menu` |
| T09_ClickConfirm | `Thank you, your order has been submitted.` |
| T10_Logout | `Sign In` |

---

## ⚙️ Runtime Settings

| Setting | Value |
|---------|-------|
| Think Time | Recorded (5 seconds via global `thinktime` variable in `globals.h`) |
| Iterations | 1 (increase for load runs) |
| Log Level | Extended logging with parameter substitution |
| Browser Emulation | Firefox 148.0 (custom user agent) |
| HTTP Version | 1.1 |
| Keep-Alive | Enabled |
| SSL Version | AUTO |
| Screen Resolution | 1920 × 1080 |

---

## 🧪 Development

### Adding More Test Users

To add more users for load testing, append rows to `p_username.dat` following the same comma-delimited format:

```
username,password,cardType,cardNumber,expiryDate,firstName,lastName,address1,address2,city,state,zip,country
```

> Ensure each user account is pre-registered on the JPetStore application before running the test.

### Updating the Target Environment

```bash
# Edit p_URL.dat and replace the existing URL
https://your-jpetstore-environment.com
```

### Adjusting Think Time

Edit `globals.h` and update the `thinktime` variable:

```c
int thinktime = 3;   // Change to desired think time in seconds
```

---

## 🐛 Troubleshooting

**HTTP 500 errors or session drops during replay**
```
Check that c_jessionid correlation is working correctly.
Verify boundary strings: LB=JSESSIONID=  RB=; Path
JSESSIONID must be appended to all post-login URLs.
```

**Login form rejected (username/password not accepted)**
```
The __fp and _sourcePage values change with every session.
Verify c_fp and c_sourcePage boundaries still match the Sign In page response.
```

**No products or items found after category navigation**
```
c_productID and c_itemID use Ordinal=All — confirm the category page
returned product links with the expected boundary LB=productId=
```

**Checkout form submission fails at T08**
```
Verify c_fpID and c_sourcePageID were captured from the checkout page in T07.
These are separate parameters from the login-page __fp and _sourcePage values.
```

**Script compiles but replay fails immediately**
```
Confirm https://petstore.octoperf.com is accessible in a browser.
The OctoPerf demo site may occasionally be unavailable or slow.
```

---

## 📖 Documentation

- [LoadRunner VuGen User Guide](https://admhelp.microfocus.com/vugen/)
- [Web HTTP/HTML Protocol Reference](https://admhelp.microfocus.com/vugen/en/latest/help/function_reference/Content/wwhelp/wwhimpl/js/html/wwhelp.htm)
- [Correlation in LoadRunner](https://admhelp.microfocus.com/vugen/en/latest/help/Content/VuGen/c_correlation.htm)
- [JPetStore Demo Application](https://petstore.octoperf.com)

---

## ⚠️ Known Considerations

- The JPetStore OctoPerf instance (`https://petstore.octoperf.com`) is a **public demo site**. Do not run heavy load tests against it — use it for single-user VuGen replay and small-scale scenarios only.
- `JSESSIONID` correlation is critical. If replay fails with HTTP 500 errors, check that the correlation boundaries (`LB=JSESSIONID=`, `RB=; Path`) still match the server response.
- The `_sourcePage` and `__fp` values change with every session and must be correlated **separately** for both the login form (T02) and the checkout form (T08).
- `p_orderID` is captured from the confirmation page but not used in subsequent requests — it is available for logging or downstream validation purposes.

---

## 🤝 Contributing

This is a performance testing practice project built on the JPetStore demo application. Contributions, additional scenarios, and improvements are welcome!

---

## 📄 License

For learning and performance testing practice purposes only.

---

Built with ❤️ for Performance Testing

Made with: **LoadRunner** • **VuGen** • **Web HTTP/HTML** • **JPetStore** • **OctoPerf**
