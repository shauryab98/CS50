<?php
    include("../includes/config.php");
    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $shares = $_POST['shares'];
        if(!preg_match("/^\d+$/",$shares))
        {
            apologize("You must enter a posive integer.");
        } 
        $stock = lookup($_POST['symbol']);
        if($stock === false)
        {
            apologize("Couldn't find a stock for that symbol.");
        }  
        $query = query("select (cash) from users where id = ?",$_SESSION['id']);
        if($query === false)
        {
            apologize("Error while buying. Please try again.");
        } 
        $cash = $query[0]['cash'];
        if($shares*$stock['price']>$cash)
        {
            apologize("You can't afford that right now.");
        }
        $query = query("UPDATE users SET cash = cash - ? WHERE id = ?",$shares*$stock['price'],$_SESSION["id"]);
        if($query === false)
        {
            apologize("Error. Please try again.");
        }
        $query = query("Insert into portfolio (symbol,id,shares) VALUES (?,?,?) ON DUPLICATE KEY UPDATE shares = shares + $shares",strtoupper($stock['symbol']),$_SESSION['id'],$shares);
        if($query === false)
        {
            apologize("Error. Please trye again.");
        }
        $date = date('m/d/Y h:i:s a',time());
        $type = "buy";
        query("INSERT INTO transactions (id,type,symbol,price,shares,date) values({$_SESSION['id']},?,?,{$stock['price']},$shares,?)",$type,$stock['symbol'],$date);
        redirect("/");
    }
    else
    {
        render("buy_form.php",["title"=>"Buy some shares"]);   
    }
?>
