<div>
    <ul id="nav_main">
        <li><a href="index.php" id="current_page">Portfolio</a></li>
        <li><a href="quote.php">Quote</a></li>
        <li><a href="buy.php">Buy</a></li>
        <li><a href="sell.php">Sell</a></li>
        <li><a href="history.php">History</a></li>
        <li><a href="change_password.php">Change Password</a></li>
        <li><a href="logout.php">Logout</a></li>
    </ul>
</div>
<div>
    <table id="portfolio_table">
        <tr>
            <td>Symbol</td>
            <td>Name</td>
            <td>Price</td>
            <td>Shares</td>
            <td>Total</td>
      </tr>
    <?php
        foreach($positions as $position)
        {
            print("<tr>");
            print("<td>{$position['symbol']}</td>");
            print("<td>{$position['name']}</td>");
            print("<td>\$".number_format($position['price'],2)."</td>");
            print("<td>{$position['shares']}</td>");
            $total = number_format($position["shares"]*$position["price"],2);
            print("<td>\${$total}</td></tr>");
        }
    ?>
        <tr>
            <td colspan=4>CASH</td>
            <td><?php print($cash);?></td>
        </tr>
    </table>
</div>
