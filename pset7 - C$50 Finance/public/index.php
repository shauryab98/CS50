<?php

    // configuration
    require("../includes/config.php"); 
    
    $stocks = query("Select * from portfolio where id = ?",$_SESSION["id"]);
    if($stocks === false)
    {
        apologize("Unable to get your stocks.");
    }
    $positions = [];
    foreach($stocks as $stock)
    {
        global $positions;
        $details = lookup($stock["symbol"]);
        $details["shares"] = $stock["shares"];
        $positions[] = $details;
    }
    $person = query("select (cash) from users where id=?",$_SESSION["id"]);
    // render portfolio     
    render("portfolio.php", ["title" => "Portfolio","positions"=>$positions,"cash"=>"\$".number_format($person[0]["cash"],2)]);
?>
