# Sith-Trader
## Algorithmic Trader Project

This project implements an algorithmic trading system that processes stock market data, makes trading decisions, and executes orders efficiently. The project is divided into three phases, progressively adding complexity from basic trade execution to statistical arbitrage across markets.

## Phase 1: Trading Strategies

Focuses on decision-making based on available trade data without execution.

Buying Low, Selling High: Tracks stock prices and buys when prices are low, sells when they are high.

Arbitrage: Detects profitable trading loops in stock combinations.

Order Book Processing: Maintains an order book and processes trades efficiently.

## Phase 2: Market and Execution
Implements the execution aspect of trading decisions.

Market Simulation: Processes trade orders based on priority (price, time, order) and expiration rules.

Market Making Strategy: Places orders to optimize execution and profit while ensuring no self-arbitrage.

## Phase 3: Statistical Arbitrage
Expands the trading strategy across multiple markets.

Cross-market Arbitrage: Detects price discrepancies across different markets and places trades accordingly.

Market Synchronization: Manages multiple order books and synchronizes trading decisions.

## Implementation Details
Input orders are read from data.txt and processed according to the phase.

Orders are executed based on priority and expiration rules.

Arbitrage opportunities are identified and executed for profit.

Statistical arbitrage extends trading across multiple markets.

