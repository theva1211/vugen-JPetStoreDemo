Action()
{

	web_set_max_html_param_len("999");
	
	web_set_sockets_option("SSL_VERSION", "AUTO");

	web_reg_save_param_ex("ParamName=c_jessionid", "LB=JSESSIONID=", "RB=; Path", LAST);
	
	web_reg_find("Text=Sign In", LAST);
	
	lr_start_transaction("JpetStore_S01_PurchaseAnimal_T01_Launch");

	web_url("Catalog.action", 
		"URL={p_URL}/actions/Catalog.action", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("JpetStore_S01_PurchaseAnimal_T01_Launch",LR_AUTO);
	
	lr_think_time(thinktime);
	
	web_reg_save_param_ex("ParamName=c_fp", "LB=__fp\" value=\"", "RB=\" /></div>", LAST);
	web_reg_save_param_ex("ParamName=c_sourcePage", "LB=_sourcePage\" value=\"", "RB=\" /><input type", LAST);
	
	lr_start_transaction("JpetStore_S01_PurchaseAnimal_T02_Login");

	web_url("Sign In", 
		"URL={p_URL}/actions/Account.action;jsessionid={c_jessionid}?signonForm=", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={p_URL}/actions/Catalog.action", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);

	web_reg_find("Text=Welcome {p_FirstName}", LAST);

	web_submit_data("Account.action", 
		"Action={p_URL}/actions/Account.action", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={p_URL}/actions/Account.action;jsessionid={c_jessionid}?signonForm=", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={p_username}", ENDITEM, 
		"Name=password", "Value={p_pwd}", ENDITEM, 
		"Name=signon", "Value=Login", ENDITEM, 
		"Name=_sourcePage", "Value={c_sourcePage}", ENDITEM, 
		"Name=__fp", "Value={c_fp}", ENDITEM, 
		LAST);

	lr_end_transaction("JpetStore_S01_PurchaseAnimal_T02_Login",LR_AUTO);

	lr_think_time(thinktime);
	
	web_reg_save_param_ex("ParamName=c_productID", "LB=productId=", "RB=\">", "Ordinal=All", LAST);

	web_reg_find("Text=Product ID", LAST);
	
	lr_start_transaction("JpetStore_S01_PurchaseAnimal_T03_Navigate_PetAnimal");

	web_url("sm_dogs.gif", 
		"URL={p_URL}/actions/Catalog.action?viewCategory=&categoryId={p_AnimalName}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={p_URL}/actions/Catalog.action", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("JpetStore_S01_PurchaseAnimal_T03_Navigate_PetAnimal",LR_AUTO);

	lr_think_time(thinktime);
	
	strProductID=lr_paramarr_random("c_productID");
	lr_save_string(strProductID, "strProductID");
	
	web_reg_save_param_ex("ParamName=c_itemID", "LB=itemId=", "RB=\">", "Ordinal=All", LAST);
	
	web_reg_find("Text=Item ID", LAST);
	
	lr_start_transaction("JpetStore_S01_PurchaseAnimal_T04_Select_ProductID");

	web_url("{strProductID}", 
		"URL={p_URL}/actions/Catalog.action?viewProduct=&productId={strProductID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={p_URL}/actions/Catalog.action?viewCategory=&categoryId={p_AnimalName}", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("JpetStore_S01_PurchaseAnimal_T04_Select_ProductID",LR_AUTO);

	lr_think_time(thinktime);
	
	strItemID=lr_paramarr_random("c_itemID");
	lr_save_string(strItemID, "strItemID");
	
	lr_start_transaction("JpetStore_S01_PurchaseAnimal_T05_Select_ItemID");

	web_reg_find("Text=Add to Cart", LAST);
	
	web_url("{strItemID}", 
		"URL={p_URL}/actions/Catalog.action?viewItem=&itemId={strItemID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={p_URL}/actions/Catalog.action?viewProduct=&productId={strProductID}", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("JpetStore_S01_PurchaseAnimal_T05_Select_ItemID",LR_AUTO);

	lr_think_time(thinktime);
	
	web_reg_find("Text=Proceed to Checkout", LAST);
	
	lr_start_transaction("JpetStore_S01_PurchaseAnimal_T06_AddToCart");

	web_url("Add to Cart", 
		"URL={p_URL}/actions/Cart.action?addItemToCart=&workingItemId={strItemID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={p_URL}/actions/Catalog.action?viewItem=&itemId={strItemID}", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("JpetStore_S01_PurchaseAnimal_T06_AddToCart",LR_AUTO);
	
	lr_think_time(thinktime);
	
	web_reg_save_param_ex("ParamName=c_fpID", "LB=__fp\" value=\"", "RB=\" /></div>", LAST);
	web_reg_save_param_ex("ParamName=c_sourcePageID", "LB=_sourcePage\" value=\"", "RB=\" /><input type", LAST);
	
	web_reg_find("Text=Ship to different address...", LAST);
	
	lr_start_transaction("JpetStore_S01_PurchaseAnimal_T07_ProceedToCheckOut");
	
	web_url("Proceed to Checkout", 
		"URL={p_URL}/actions/Order.action?newOrderForm=", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={p_URL}/actions/Cart.action?addItemToCart=&workingItemId={strItemID}", 
		"Snapshot=t10.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("JpetStore_S01_PurchaseAnimal_T07_ProceedToCheckOut",LR_AUTO);

	lr_think_time(thinktime);
	
	web_reg_find("Text=Return to Main Menu", LAST);
	
	lr_start_transaction("JpetStore_S01_PurchaseAnimal_T08_ClickContinue");

	web_submit_data("Order.action", 
		"Action={p_URL}/actions/Order.action", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={p_URL}/actions/Order.action?newOrderForm=", 
		"Snapshot=t11.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=order.cardType", "Value={p_cardType}", ENDITEM, 
		"Name=order.creditCard", "Value={p_cardNumber}", ENDITEM, 
		"Name=order.expiryDate", "Value={p_expiryDate}", ENDITEM, 
		"Name=order.billToFirstName", "Value={p_FirstName}", ENDITEM, 
		"Name=order.billToLastName", "Value={p_LastName}", ENDITEM, 
		"Name=order.billAddress1", "Value={p_Address1}", ENDITEM, 
		"Name=order.billAddress2", "Value={p_Address2}", ENDITEM, 
		"Name=order.billCity", "Value={p_City}", ENDITEM, 
		"Name=order.billState", "Value={p_State}", ENDITEM, 
		"Name=order.billZip", "Value={p_Zip}", ENDITEM, 
		"Name=order.billCountry", "Value={p_Country}", ENDITEM, 
		"Name=newOrder", "Value=Continue", ENDITEM, 
		"Name=_sourcePage", "Value={c_sourcePageID}", ENDITEM, 
		"Name=__fp", "Value={c_fpID}", ENDITEM, 
		LAST);

	lr_end_transaction("JpetStore_S01_PurchaseAnimal_T08_ClickContinue",LR_AUTO);

	lr_think_time(thinktime);
	
	web_reg_save_param_ex("ParamName=p_orderID","LB=Order #","RB=\n",LAST);
	
	web_reg_find("Text=Thank you, your order has been submitted.", LAST);
	
	lr_start_transaction("JpetStore_S01_PurchaseAnimal_T09_ClickConfirm");

	web_url("Confirm", 
		"URL={p_URL}/actions/Order.action?newOrder=&confirmed=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={p_URL}/actions/Order.action", 
		"Snapshot=t12.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("JpetStore_S01_PurchaseAnimal_T09_ClickConfirm",LR_AUTO);

	lr_think_time(thinktime);
	
	web_reg_find("Text=Sign In", LAST);
	
	lr_start_transaction("JpetStore_S01_PurchaseAnimal_T10_Logout");

	web_url("Sign Out", 
		"URL={p_URL}/actions/Account.action?signoff=", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={p_URL}/actions/Order.action?newOrder=&confirmed=true", 
		"Snapshot=t13.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("JpetStore_S01_PurchaseAnimal_T10_Logout",LR_AUTO);

	return 0;
}