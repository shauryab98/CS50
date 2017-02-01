<div>
    <ul id="nav_main">
        <li><a href="index.php">Portfolio</a></li>
        <li><a href="quote.php">Quote</a></li>
        <li><a href="buy.php">Buy</a></li>
        <li><a href="sell.php">Sell</a></li>
        <li><a href="history.php" id="current_page">History</a></li>
        <li><a href="change_password.php">Change Password</a></li>
        <li><a href="logout.php">Logout</a></li>
    </ul>
</div>

<div>
    <table id="history_table">
        <tr>
            <td>Transaction</td>
            <td>Date/Time</td>
            <td>Symbol</td>
            <td>Shares</td>
            <td>Price</td>
      </tr>
    <?php
        foreach($history as $item)
        {
            print("<tr>");
            print("<td>{$item['type']}</td>");
            print("<td>{$item['date']}</td>");            
            print("<td>{$item['symbol']}</td>");
            print("<td>{$item['shares']}</td>");
            print("<td>\$".number_format($item['price'],2)."</td></tr>");            
        }
    ?>
    </table>
</div>
