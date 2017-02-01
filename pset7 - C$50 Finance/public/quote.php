<?php

include("../includes/config.php");

if($_SERVER["REQUEST_METHOD"] == "POST")
{
    $stock = lookup($_POST["symbol"]); 
    if($stock!==false)
    {
        $message = "A share of ". $stock['name']."{$stock['symbol']} "."costs <b>\$".number_format($stock['price'],2)."</b>";
        render("stock_price.php",["title"=>"Stock Lookup","price"=>$message]);    
    } 
    else
    {
        apologize("Couldn't find a stock for that symbol.");
    }
    
        
}
else
{
    render("stock_search.php",["title"=>"Look for a stock"]);
}


?>
