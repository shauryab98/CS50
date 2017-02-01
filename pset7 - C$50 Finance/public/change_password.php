<?php

    //configuration
    require("../includes/config.php");
    
    //if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {   
        if (empty($_POST["curr_password"]))
        {
            apologize("You need to enter your current password.");
        }
        else if(empty($_POST["new_password"]))
        {
            apologize("Please enter a new password.");
        }
        else if($_POST["new_password"] !== $_POST["confirm_new_password"])
        {
            apologize("Your new passwords do not match");
        }
        $query = query("Select (hash) from users where id = ?",$_SESSION['id']);
        if($query === false)
        {
            apologize("There was an error while completing your request! Please try again.");
        }
        $password_hash = $query[0]['hash'];
        if (crypt($_POST["curr_password"], $password_hash) != $password_hash)
        {
            apologize("Your current password is wrong.");
        }   
        else
        {
            $success = query("UPDATE users SET hash = ? where id = ?",crypt($_POST["new_password"]),$_SESSION['id']);
            if($success===false)
            {
                apologize("Error while changing password. Please try again.");
            }
            else
            {
                redirect("index.php");
            }
        }
    }
    else
    {
        //else render form
        render("change_password_form.php", ["title" => "Change Password"]);
    }
    
