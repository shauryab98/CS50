<?php
    include("../includes/config.php");
    $query = query("SELECT * from transactions where id = ?",$_SESSION['id']);
    if($query === false)
    {
        apologize("Couldn't retrieve history. Please try again.");
    }
    render("show_history.php",["history"=>$query]);
?>
