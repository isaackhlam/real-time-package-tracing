<template>
  <div class="tracking-app">
    <header class="app-header">
      <h1>Real-Time Package Tracking</h1>
    </header>
    <main class="app-content">
      <img src="../../DALL·E.png" alt="Package Tracking Visualization" class="tracking-image"/>
      <p>Welcome to the ultimate logistic experience. Our GPS-enabled tracking system offers you real-time updates on your packages, anywhere, anytime. Stay informed from the moment your package is dispatched to the instant it arrives at your doorstep. Our sophisticated technology ensures that you are always in the loop, providing peace of mind for your important deliveries.</p>
    </main>
  </div>
</template>

<style scoped>
.tracking-app {
  display: flex;
  flex-direction: column;
  min-height: 100vh;
  justify-content: flex-start;
  align-items: center;
  background-color: #f2f2f2;
}

.app-header {
  width: 100%;
  background-color: #4CAF50;
  color: white;
  padding: 20px 0;
  text-align: center;
  box-shadow: 0 4px 6px rgba(0,0,0,0.1);
}

.app-header h1 {
  margin: 0;
  font-size: 2.5rem;
}

.app-content {
  text-align: center;
  padding: 20px;
  max-width: 800px; /* Set a max-width for better readability on larger screens */
  font-size: 1.1rem;
}

.app-content {
  text-align: center;
  padding: 20px;
  max-width: 800px; /* Set a max-width for better readability on larger screens */
}

.tracking-image {
  max-width: 80%;
  height: auto;
  border-radius: 8px; /* Optional: adds rounded corners to the image */
  margin-bottom: 20px; /* Adds space between the image and the text */
}
</style>
