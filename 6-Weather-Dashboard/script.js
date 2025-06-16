// API Configuration
const API_KEY = '13761eca11f916c30293d7dad5e0a3bb'; // Replace with your OpenWeatherMap API key
const BASE_URL = 'https://api.openweathermap.org/data/2.5';

// DOM Elements
const searchInput = document.getElementById('search-input');
const searchBtn = document.getElementById('search-btn');
const searchHistory = document.querySelector('.search-history');
const cityName = document.getElementById('city-name');
const date = document.getElementById('date');
const temp = document.getElementById('temp');
const weatherDesc = document.getElementById('weather-desc');
const wind = document.getElementById('wind');
const humidity = document.getElementById('humidity');
const pressure = document.getElementById('pressure');
const weatherImg = document.getElementById('weather-img');

// Initialize
document.addEventListener('DOMContentLoaded', () => {
    // Load recent searches from localStorage
    loadRecentSearches();
    
    // Set current date
    updateDate();
    
    // Add event listeners
    searchBtn.addEventListener('click', handleSearch);
    searchInput.addEventListener('keypress', (e) => {
        if (e.key === 'Enter') handleSearch();
    });
});

// Update current date
function updateDate() {
    const now = new Date();
    const options = { weekday: 'long', day: 'numeric', month: 'long', year: 'numeric' };
    date.textContent = now.toLocaleDateString('en-US', options);
}

// Handle search
async function handleSearch() {
    const city = searchInput.value.trim();
    if (!city) return;

    try {
        // Get weather data
        const weatherData = await getWeatherData(city);
        updateWeatherUI(weatherData);
        
        // Add to recent searches
        addToRecentSearches(city);
        
        // Clear input
        searchInput.value = '';
    } catch (error) {
        console.error('Error fetching weather data:', error);
        alert('Error fetching weather data. Please try again.');
    }
}

// Get weather data from API
async function getWeatherData(city) {
    const response = await fetch(`${BASE_URL}/weather?q=${city}&units=metric&appid=${API_KEY}`);
    if (!response.ok) throw new Error('City not found');
    return await response.json();
}

// Update weather UI
function updateWeatherUI(data) {
    cityName.textContent = data.name;
    temp.textContent = `${Math.round(data.main.temp)}°C`;
    weatherDesc.textContent = data.weather[0].description;
    wind.textContent = `${data.wind.speed} km/h`;
    humidity.textContent = `${data.main.humidity}%`;
    pressure.textContent = `${data.main.pressure} hPa`;
    weatherImg.src = `https://openweathermap.org/img/wn/${data.weather[0].icon}@2x.png`;
}

// Add to recent searches
function addToRecentSearches(city) {
    let searches = JSON.parse(localStorage.getItem('recentSearches') || '[]');
    
    // Remove if already exists
    searches = searches.filter(item => item !== city);
    
    // Add to beginning
    searches.unshift(city);
    
    // Keep only last 5 searches
    searches = searches.slice(0, 5);
    
    // Save to localStorage
    localStorage.setItem('recentSearches', JSON.stringify(searches));
    
    // Update UI
    loadRecentSearches();
}

// Load recent searches
function loadRecentSearches() {
    const searches = JSON.parse(localStorage.getItem('recentSearches') || '[]');
    searchHistory.innerHTML = searches.map(city => `
        <button class="recent-search" onclick="searchInput.value = '${city}'; handleSearch();">
            ${city}
        </button>
    `).join('');
}

// Add some CSS for recent search buttons
const style = document.createElement('style');
style.textContent = `
    .recent-search {
        background: var(--background);
        border: none;
        padding: 0.5rem 1rem;
        border-radius: 0.5rem;
        cursor: pointer;
        transition: var(--transition);
        text-align: left;
        width: 100%;
    }
    
    .recent-search:hover {
        background: var(--primary-color);
        color: white;
    }
`;
document.head.appendChild(style); 