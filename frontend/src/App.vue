<template>

  <v-app id="inspire">
    <v-navigation-drawer
      clipped
      temporary
      v-model="drawer"
      enable-resize-watcher
      app
    >
      <v-list two-line>
        <router-link :to="{name: 'cocktails'}" tag="v-list-tile" active-class="active" exact>
          <v-list-tile-action>
            <img src="./assets/refreshing-drink-glass-with-fruit-slice-straw-and-an-umbrella-decoration.svg" alt="cocktails">
          </v-list-tile-action>
          <v-list-tile-content>
            <v-list-tile-title>Cocktails</v-list-tile-title>
          </v-list-tile-content>
        </router-link>
        <router-link :to="{name: 'ingredients'}" tag="v-list-tile" active-class="active" exact>
          <v-list-tile-action>
            <img src="./assets/picnic-basket-full-of-raw-vegetables.svg" alt="ingredients">
          </v-list-tile-action>
          <v-list-tile-content>
            <v-list-tile-title>Ingredients</v-list-tile-title>
          </v-list-tile-content>
        </router-link>
        <router-link :to="{name: 'settings'}" tag="v-list-tile" active-class="active" exact>
          <v-list-tile-action>
            <img src="./assets/ingredients-list.svg" alt="settings">
          </v-list-tile-action>
          <v-list-tile-content>
            <v-list-tile-title>Settings</v-list-tile-title>
          </v-list-tile-content>
        </router-link>
      </v-list>
    </v-navigation-drawer>
    <v-toolbar app fixed clipped-left>
      <v-toolbar-side-icon @click.stop="drawer = !drawer"></v-toolbar-side-icon>
      <v-toolbar-title>Bar-Omatic</v-toolbar-title>
    </v-toolbar>
    <main>
      <v-content>
        <router-view></router-view>
      </v-content>
    </main>
  </v-app>
</template>

<script>
export default {
  name: 'app',
  data: () => ({
    drawer: true
  })
}
</script>

<style>


body {
  font-family: 'Architects Daughter', cursive;
  font-size: 16pt;
}

.navigation-drawer>.list:not(.list--dense) .list__tile,
.input-group--text-field input, .input-group--text-field textarea,
.btn {
  font-size: 16pt;
}

 @font-face {
     font-family: 'Montserrat';
     src: url('/static/fonts/Montserrat-Regular.otf');
     font-weight: normal;
 }

 @font-face {
     font-family: 'Montserrat';
     src: url('/static/fonts/Montserrat-Bold.otf');
     font-weight: bold;
 }

 #view {
     font-family: 'Montserrat', Helvetica, Arial, sans-serif;
     position: absolute;
     top: 50px;
     bottom: 0px;
     width: 100%;
     overflow: auto;
 }

</style>
