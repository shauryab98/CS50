<?php
    include("../includes/config.php");
    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $sell = $_POST["sell_choice"];
        if(empty($sell))
        {   
            apologize("You need to select a stock to sell.");       
        }    
        else
        {
            $stock = lookup($sell);   
            if($stock === false)
            {
                apologize("Error. Please try again.");
            }
            $query = query("SELECT (shares) from portfolio where id = ? and symbol = ?",$_SESSION["id"],$sell);
            if($query===false)
            {
                apologize("Error. Please try again.");
            }
            $shares = $query[0]["shares"]; 
            $money =  $shares * $stock['price'];
            $query = query("delete from portfolio where id = ? and symbol = ?",$_SESSION["id"],$sell);
            if($query===false)
            {
                apologize("Error. Please try again.");
            }
            $query = query("UPDATE users SET cash = cash + $money WHERE id = ?",$_SESSION['id']);
            $date = date('m/d/Y h:i:s a',time());
            $type = "sell";
            query("INSERT INTO transactions (id,type,symbol,price,shares,date) values({$_SESSION['id']},?,?,{$stock['price']},$shares,?)",$type,$stock['symbol'],$date);
            redirect("/");
        }
    }
    else
    {
        $stocks = query("SELECT (symbol) FROM portfolio where id = ?",$_SESSION["id"]);
        if($stocks === false)
        {
            apologize("Couldn't load your stocks.");
        }
        render("sell_form.php",['title'=>"Sell some stocks","stocks"=>$stocks]);
    }
?>
