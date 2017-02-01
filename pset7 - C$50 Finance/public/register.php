<?php

    //configuration
    require("../includes/config.php");
    
    //if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {   
        //TODO
        if (empty($_POST["username"]))
        {
            apologize("You need to enter your username.");
        }
        else if ($_POST["password"] == "")
        {
            apologize("You need to enter your password");
        }
        else if($_POST["confirmation"] !== $_POST["password"])
        {
            apologize("Your passwords do not match");
        }   
        else
        {
            $success = query("INSERT INTO users(username,hash,cash) values(?,?,10000.00)",$_POST["username"],crypt($_POST["password"]));
            if($success===false)
            {
                apologize("Error while registering. Please try again.");
            }
            else
            {
                $rows = query("SELECT LAST_INSERT_ID() AS id");
                $id = $rows[0]["id"];
                $_SESSION["id"] = $id;
                redirect("index.php");
            }
        }
    }
    else
    {
        //else render form
        render("register_form.php", ["title" => "Register"]);
    }
    
